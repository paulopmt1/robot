var serverAddress = 'http://54.94.244.175';
var serverPort = 3001;
var serialPort = '/dev/ttyAMA0';

var socket = require('socket.io-client')(serverAddress + ':' + serverPort);

socket.on('connect', function(){
    socket.emit('identify', {
        type: 'robot'
    });
});

socket.on('event', function(data){});
socket.on('disconnect', function(){});

var lastSerialMessage = '';

socket.on('userCommand', function(msg){
  console.log("Recebido do servidor: " + msg);
  sendToSerial(msg);
});

var SerialPort = require("serialport");
var port = new SerialPort(serialPort, {
  baudRate: 115200,
  parser: SerialPort.parsers.readline('\n')
});

port.on('open', function() {
    console.log('Porta ' + serialPort + ' aberta com sucesso!');
    console.log('Testando conexão com Arduino...');
    sendToSerial('OI');
});
 
// open errors will be emitted as an error event 
port.on('error', function(err) {
  console.log('Erro ao escrever na porta ' + serialPort + ':', err.message);
});

port.on('data', function(data){
    if (data == "OI"){
      console.log('Comunicação com Arduino está 100%!');
    }
  
    console.log("Recebido da serial: " + data);
    socket.emit('robotData', data);
  
  
});

var sendToSerial = function(msg){
  port.write(msg , function(err) {
      if (err){
          console.log("Erro na serial: ");
          console.log(err.message);
      }else{
          console.log('Comando enviado com sucesso: ' + msg);
      }
  });
};