var fs = require('fs');
var PeerServer = require('peer').PeerServer;

var server = PeerServer({
	  port: 9000,
	  debug: true,
			path: 'teste',
	  ssl: {
		      key: fs.readFileSync('/var/www/html/robot/serverhttps/robot.paulotrentin.com.br/privkey1.pem'),
		      cert: fs.readFileSync('/var/www/html/robot/serverhttps/robot.paulotrentin.com.br/fullchain1.pem')
		    }
});
