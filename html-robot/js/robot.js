var socket, lastOnlineTime = 0, ROBOT_ONLINE_TIMEOUT = 1000;

	var init = function(serverAddress){
		socket = io(serverAddress);

                socket.on('connect', function(){
                    socket.emit('identify', {
                        type: 'html-client'
                    });
                });

		socket.on('serverStatus', function(msg){
			lastOnlineTime = new Date();
		});

		socket.on('robotData', function(msg){
			console.log(msg);

			if (msg.data.indexOf('BATERIA_PERCENTUAL') > -1){
				var statusText = msg.data.split('BATERIA_PERCENTUAL:')[1]
				$('.battery-icon .status').html(statusText + '%');
			}
		});
	}


	$(document).ready(function(){
		$('.powerup').click(function(){
			socket.emit('userCommand', {'command':'LIGAR_NOTEBOOK'});
		});


		init("robot.paulotrentin.com.br:3002");

		$('#serverAddress').change(function(){
			if (socket){
				socket.close();
			}

			init($(this).val());
		}).change();
		

		var checkRobotIsOnline = function(){

			var diff = new Date() - lastOnlineTime;

			if (diff > ROBOT_ONLINE_TIMEOUT){
				isOnline = false;
			}else{
				isOnline = true;
			}

			if (isOnline){
				$('#status img').removeClass('disabled');
			}else{
				$('#status img').addClass('disabled');
			}
		};

		setInterval(function(){
			checkRobotIsOnline();
		},150);



		var statusInterval = false;
		var setStatus = function(status){
			clearInterval(statusInterval);

			$('#connectionStatus').html(status);
			$('#connectionStatus').fadeIn(50);

			statusInterval = setTimeout(function(){
				$('#connectionStatus').fadeOut();
			}, 1000)
		}

		setInterval(function(){
			//socket.emit('userCommand', {'command':'BATERIA'});
		},5000);

		$('#status img').on('click', function(){
			socket.emit('userCommand', {'command':'LIGAR_NOTEBOOK'})
		});

		$('#webcamRange').on('change', function(){
			socket.emit('userCommand', {'command':'MOVE_WEBCAM:' + $(this).val()})
		});


		$('.btn').click(function(){

			/*if ( ! isOnline){
				setStatus('Robô está offline');
				return;
			}*/

			var command = $(this).attr('command');
			socket.emit('userCommand', command);
		});
                
                $(document).keydown(function(data){
                    console.log(data.keyCode)
                    
                    switch (data.keyCode){
                        case 87:
                        case 38:
                            data.preventDefault();
                            socket.emit('userCommand', '|W');
                            break;
                            
                        case 83:
                        case 40:
                            data.preventDefault();
                            socket.emit('userCommand', '|S');
                            break;
                            
                        case 65:
                        case 37:
                            data.preventDefault();
                            socket.emit('userCommand', '|A');
                            break;
                            
                        case 68:
                        case 39:
                            data.preventDefault();
                            socket.emit('userCommand', '|D');
                            break;
                    }
                    
                });

	});