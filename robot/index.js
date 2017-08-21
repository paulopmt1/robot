var serverAddress = 'http://54.94.244.175';
var serverPort = 3000;
var serialPort = '/dev/ttyAMA0';

var socket = require('socket.io-client')(serverAddress + ':' + serverPort);
socket.on('connect', function(){});
socket.on('event', function(data){});
socket.on('disconnect', function(){});

var lastSerialMessage = '';

socket.on('userCommand', function(msg){
  console.log("Recebido do servidor: " + msg);
  sendToSerial(msg);
});

var SerialPort = require("serialport");
var port = new SerialPort(serialPort, {
  baudRate: 9600,
  parser: SerialPort.parsers.readline('\n')
});

port.on('open', function() {
  port.write('main screen turn on', function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('message written');
  });
});
 
// open errors will be emitted as an error event 
port.on('error', function(err) {
  console.log('Erro ao escrever na porta ' + serialPort + ':', err.message);
});

port.on('data', function(data){
  console.log("Recebido da serial: " + data);
  socket.emit('robotData', data);
});

var sendToSerial = function(msg){
  port.write(msg);
};