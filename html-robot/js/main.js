var toCall = false;
var displayType = 'robot';

    // Compatibility shim
    navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia;
    var id = document.location.hash;

    if (document.location.hash.split('/').length > 1){
      id = document.location.hash.split('/')[0];
      toCall = document.location.hash.split('/')[1];

      displayType = 'html-client';
    }

    id = id.replace('#','');

    // PeerJS object
    var peer = new Peer(id, { key: 'peerjs', debug: 3, host: 'robot.paulotrentin.com.br', path: 'teste'});

    $(document).dblclick(function(){
      $("#topmenu").toggle();
    })

    if (displayType == 'robot'){
      $("#topmenu").hide();
    }


    //var peer = new Peer('someid', {host: 'localhost', port: 9000, path: '/myapp'});

    /*var peer = new Peer({
	  config: {'iceServers': [
	    { url: 'stun:stun.l.google.com:19302' },
	    { url: 'turn:homeo@turn.bistri.com:80', credential: 'homeo' }
	  ]} 
	});*/

    peer.on('open', function(){
      $('#my-id').text(peer.id);

      setTimeout(function(){
        if (toCall){
          var call = peer.call(toCall, window.localStream);
          step3(call);
        }
      }, 1000);
      
    });

    // Receiving a call
    peer.on('call', function(call){
      // Answer the call automatically (instead of prompting user) for demo purposes
      call.answer(window.localStream);
      step3(call);
    });
    peer.on('error', function(err){
      alert(err.message);
      // Return to step 2 if error occurs
      step2();
    });

    // Click handlers setup
    $(function(){
      $('#make-call').click(function(){
        // Initiate a call!
        var call = peer.call($('#callto-id').val(), window.localStream);
        step3(call);
      });

      $('#end-call').click(function(){
        window.existingCall.close();
        step2();
      });

      // Retry if getUserMedia fails
      $('#step1-retry').click(function(){
        $('#step1-error').hide();
        step1();
      });

      
    });

    function step1 () {
      // Get audio/video stream
      navigator.getUserMedia({audio: true, video: true}, function(stream){
        // Set your video displays
        $('#my-video').prop('src', URL.createObjectURL(stream));

        window.localStream = stream;
        step2();
      }, function(){ $('#step1-error').show(); });
    }

    function step2 () {
      $('#step1, #step3').hide();
      $('#step2').show();
    }

    function step3 (call) {
      // Hang up on an existing call if present
      if (window.existingCall) {
        window.existingCall.close();
      }

      // Wait for stream on the call, then set peer video display
      call.on('stream', function(stream){
        $('#their-video').prop('src', URL.createObjectURL(stream));
      });

      // UI stuff
      window.existingCall = call;
      $('#their-id').text(call.peer);
      call.on('close', step2);
      $('#step1, #step2').hide();
      $('#step3').show();
    }







function handleError(error) {
  console.log('navigator.getUserMedia error: ', error);
}


function gotStream(stream) {
  window.stream1 = stream; // make stream available to console
  $('#my-video').prop('src',  URL.createObjectURL(stream));


  if (displayType == 'html-client'){
    window.localStream = stream;
    step2();
  }else{
    navigator.mediaDevices.getUserMedia({
      audio: {deviceId: false},
      video: {
        deviceId: localStorage.bottomCamera,
        width: { ideal: 640 },
        height: { ideal: 480 }
      }
    }).then(gotStream2).catch(handleError);
  }
    
}

function gotStream2(stream) {
  window.stream2 = stream;

  // Composite videos
  composite = new VideoStreamMerger({
    width: 1280,
    height: 720
  })
  composite.addStream(window.stream1, {
    x: 0,
    y: 0,
    width: composite.width,
    height: composite.height
  })

  console.log('largura: ' + composite.width)
  var bottomCameraWidth = composite.width * 20 / 100;

  composite.addStream(window.stream2, {
    //x: composite.width - 50,
    y: composite.height - 240,
    width: 320,
    height: 240
  });
  composite.start()
  //videoElement.srcObject = composite.result;


  // Set your video displays
	$('#my-video').prop('src', URL.createObjectURL(composite.result));

	window.localStream = composite.result;
	step2();

}


function setBottomCameraSize(bottomCameraSize){
  if (displayType == 'html-client'){
    return;
  }

  composite.removeStream(window.stream2);
  var newWidth, newHeight;

  switch(bottomCameraSize){
    case 'p':
      newWidth = 106;
      newHeight = 80;
      break;

    case 'm':
      newWidth = 320;
      newHeight = 240;
      break;

    case 'g':
      newWidth = 1024;
      newHeight = 768;
      break;
  }

  composite.addStream(window.stream2, {
    y: composite.height - newHeight,
    width: newWidth,
    height: newHeight
  });
}

function start() {
  deviceIdWebcam1 = document.getElementById('frontCamera').value;
  deviceIdWebcam2 = document.getElementById('bottomCamera').value;
  robotMic = document.getElementById('robotMic').value;

  localStorage.setItem("frontCamera", deviceIdWebcam1);
  localStorage.setItem("bottomCamera", deviceIdWebcam2);
  localStorage.setItem("robotMic", robotMic);


  //deviceIdWebcam1 = '7jWz9LpbzZytnvA/T+RAc1y+dBp8YwmaYTb/F7KyN68=';
  //deviceIdWebcam2 = 'Wk1xw9QasTA+RzLg0rFhQMhr9E9+TstLRyqm2YG4m9Q=';

  //deviceIdWebcam1 = 'Wk1xw9QasTA+RzLg0rFhQMhr9E9+TstLRyqm2YG4m9Q=';
  //deviceIdWebcam2 = 'Wk1xw9QasTA+RzLg0rFhQMhr9E9+TstLRyqm2YG4m9Q=';

  if (window.stream) {
    window.stream.getTracks().forEach(function(track) {
      track.stop();
    });
  }

  navigator.mediaDevices.getUserMedia({
    audio: {deviceId: localStorage.robotMic},
    video: {
      deviceId: localStorage.frontCamera,
      width: { ideal: 1280 },
      height: { ideal: 720 }
    }
  }).then(gotStream).catch(handleError);
  


}


$('#start').click(function(){
  start();
});


function listCameraDevices(deviceInfos) {
  console.log(deviceInfos);
  
  
  for (var i = 0; i !== deviceInfos.length; ++i) {
    var deviceInfo = deviceInfos[i];
    

    if (deviceInfo.kind === 'videoinput') {
      var option = document.createElement('option');
      option.value = deviceInfo.deviceId;
      option.text = deviceInfo.label;

      document.getElementById('frontCamera').appendChild(option);


      var option2 = document.createElement('option');
      option2.value = deviceInfo.deviceId;
      option2.text = deviceInfo.label;

      document.getElementById('bottomCamera').appendChild(option2);
    }

    if (deviceInfo.kind === 'audioinput'){
      var option2 = document.createElement('option');
      option2.value = deviceInfo.deviceId;
      option2.text = deviceInfo.label;

      document.getElementById('robotMic').appendChild(option2);
    }
  }


  if (localStorage.robotMic){
    $('#robotMic').val(localStorage.robotMic);
    $('#frontCamera').val(localStorage.frontCamera);
    $('#bottomCamera').val(localStorage.bottomCamera);
  }


  start();

}

navigator.mediaDevices.enumerateDevices().then(listCameraDevices).catch(handleError);
