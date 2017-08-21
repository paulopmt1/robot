var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var fs = require('fs');
var activeConnections = 0;

io.on('connection', function(socket){
  activeConnections++;

  var socketId = socket.id;
  var clientIp = socket.request.connection.remoteAddress;
  console.log('Novo cliente de ' + clientIp);
  
  socket.emit('userCommand', "AUTENTICADO");

  socket.on('userCommand', function(msg){
    console.log("Recebido do usuário: " + msg);
    io.emit('userCommand', msg);
  });

  socket.on('robotData', function(msg){
    console.log("Recebido do robô: " + msg);
    io.emit('robotData', msg);
  });


  socket.on('disconnect', function(){
    console.log('user disconnected');
    activeConnections--;
  });
});


app.get('/', function(req, res){
  res.send('<h1>Conexões ativas: ' + activeConnections  + '</h1>');
});

http.listen(3000, function(){
  console.log('listening on *:3000');
});