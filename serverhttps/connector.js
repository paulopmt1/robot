var socket = require('socket.io-client')('http://robot.paulotrentin.com.br:3001');
socket.on('connect', function(){
	console.log('Connectado ao server http');
});


var socket2 = require('socket.io-client')('https://127.0.0.1:3002', {secure: true, reconnect: true,rejectUnauthorized : false});
socket2.on('connect', function(){
        console.log('Connectado ao server https');
});

socket2.on('userCommand', function(data){
	console.log('user commando from https');
	socket.emit('userCommand', data);
});




socket.on('robotData', function(data){
	console.log('evento do robo http para https');
        console.log(data);

	socket2.emit('robotData', data);
});

socket.on('disconnect', function(){
console.log('se foi cara');
});


setTimeout(function(){
        console.log('teste');
        socket.emit('identify', {type:'interconnector'});
},1000);


