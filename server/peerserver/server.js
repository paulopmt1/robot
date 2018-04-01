var fs = require('fs');
var PeerServer = require('peer').PeerServer;

var server = PeerServer({
	  port: 9000,
	  debug: true,
			path: 'teste',
	  ssl: {
		      key: fs.readFileSync('/etc/apache2/ssl/phpit.key'),
		      cert: fs.readFileSync('/etc/apache2/ssl/phpit.pem')
		    }
});
