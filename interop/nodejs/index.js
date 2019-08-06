var spawn = require('child_process').spawn;
var prc = spawn('../c++/ConsoleEcho/build/consoleEcho', ['nodejs'])      //call c++
//var prc = spawn('python', ['../python/consoleEcho.py', 'nodejs'])      //call python
//var prc = spawn('java', ['-jar','../java/ConsoleEcho.jar', 'nodejs'])      //call java

//noinspection JSUnresolvedFunction
prc.stdout.setEncoding('utf8');
prc.stdout.on('data', function (data) {
    var str = data.toString()
    var lines = str.split(/(\r?\n)/g);
    console.log(lines.join(""));
});

prc.on('close', function (code) {
    console.log('process exit code ' + code);
});