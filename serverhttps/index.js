var app = require('express')();
var https = require('https');
//var io = require('socket.io')(https);
var fs = require('fs');
var activeConnections = [];

var server = https.createServer({ 
                key: fs.readFileSync('robot.paulotrentin.com.br/privkey1.pem'),
                cert: fs.readFileSync('robot.paulotrentin.com.br/fullchain1.pem') 
             },app);
server.listen(3002);

var io = require('socket.io')(server);

io.on('connection', function(socket){
  var socketId = socket.id;
  var clientIp = socket.request.connection.remoteAddress;
  
  activeConnections.push({
      id: socketId,
      ip: clientIp,
      type: 'undefined'
  });
  
  printClientsOnConsole();
  socket.emit('userCommand', "AUTENTICADO");

  socket.on('userCommand', function(msg){
    console.log("Recebido do usuário: " + msg);
    io.emit('userCommand', msg);
  });

  socket.on('robotData', function(msg){
//    console.log("Recebido do robô: " + msg);
    io.emit('robotData', msg);
  });
  
  socket.on('identify', function(msg){
      var host = findHostById(socket.id);
      host.type = msg.type;
      
      switch (msg.type){
          case 'robot':
            console.log('Temos um robô disponível!');
            break;
          case 'html-client':
            console.log('Temos um usuário disponível!');
            break;
            
          default:
            console.log('Não sei quem é este host: ' + msg.type);
      }
      
      printClientsOnConsole();
  });

  socket.on('disconnect', function(reason){
    console.log('Usuário ' + this.request.connection.remoteAddress + ' desconectado');
    removeHostFromActiveConnections(this.id);
    printClientsOnConsole();
  });
});


function removeHostFromActiveConnections(id){
    for (var i = 0; i < activeConnections.length; i++){
        if (activeConnections[i].id === id){
            activeConnections.splice(i, 1);
        }
    }
}

function findHostById(id){
    for (var i = 0; i < activeConnections.length; i++){
        if (activeConnections[i].id === id){
            return activeConnections[i];
        }
    }
    
    return false;
}

function printClientsOnConsole(){
    console.log('');
    console.log('Clientes ativos:');
    console.log(activeConnections);
};

app.get('/', function(req, response){
//    response.writeHead(200, {"Content-Type": "application/json"});
    
    var connections = JSON.stringify(activeConnections);
    response.json(activeConnections);
});

//https.listen(3002, function(){
//  console.log('listening on *:3002');
//});




