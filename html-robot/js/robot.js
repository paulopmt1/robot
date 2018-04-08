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

		setInterval(function(){
			socket.emit('userCommand', {'command':'BATERIA'});
		},5000);
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
            //console.log(data.keyCode)
            return;

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




function Input(el, eventCallback){
    var parent = el,
        map = {},
        intervals = {};


    map.ArrowRight = false;
    map.ArrowLeft = false;
    map.ArrowUp = false;
    map.ArrowDown = false;

    function ev_kdown(ev)
    {
        map[ev.key] = true;
        ev.preventDefault();
        eventCallback(map);
        return;
    }

    function ev_kup(ev)
    {
        map[ev.key] = false;
        ev.preventDefault();
        eventCallback(map);
        return;
    }

    function key_down(key)
    {
        return map[key];
    }

    function clear()
    {
        map = {};
    }

    function attach()
    {
        parent.addEventListener("keydown", ev_kdown);
        parent.addEventListener("keyup", ev_kup);
    }

    function Input()
    {
        attach();
    }

    return Input();
}


Input(document, function(keys){
	
	console.log(keys);

	if ( keys.ArrowUp && ! keys.ArrowLeft && ! keys.ArrowRight){
		console.log('frente somente');
		startCommand('|W');
	}
	else if ( ! keys.ArrowUp && ! keys.ArrowLeft && ! keys.ArrowRight && keys.ArrowDown){
		console.log('traz somente');
		startCommand('|S');
	}

	else if ( ! keys.ArrowUp && keys.ArrowLeft){
		console.log('esquerda somente');
		startCommand('|A');
	}

	else if ( ! keys.ArrowUp && keys.ArrowRight){
		console.log('direita somente');
		startCommand('|D');
	}

	else if (keys.ArrowUp && keys.ArrowRight){
		console.log('frente direita');
		//startCommand('|W');	
		//startCommand('|D');	
	}

	else if ( ! keys.ArrowUp && ! keys.ArrowLeft && ! keys.ArrowRight && ! keys.ArrowDown){
		console.log('Para tudo!');
		canSend = false;
	}

	else{
		console.log('Para tudo!');
		canSend = false;
	}


});


var canSend = false;
var commandToSend = false;

function startCommand(command){
	canSend = true;
	commandToSend = command;
}

setInterval(function(){
	if (canSend){
		console.log('enviando ' + commandToSend);
		socket.emit('userCommand', commandToSend);
	}
},30);