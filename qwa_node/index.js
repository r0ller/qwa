var express = require('express');
var app = express();
//var fs = require('fs');
//var request = require('request');
//var exec = require('child_process').exec;
//var https = require('https');
var http = require('http');
var path=require('path');
//wasm backend lib must be preloaded or when loaded just before ccall
//care must be taken to wait till it gets loaded
var backend = require('../build-qwa_pure_backend-wasm-Debug/libqwa_pure_backend.js'); 

app.use(function(req, res, next){
	res.header("Access-Control-Allow-Origin","*");
	res.header("Access-Control-Allow-Headers","Origin, X-requested-With, Content-Type, Accept");
	next();
});
//emscripten wget2 cannot send json, only urlencoded data
//app.use(express.json());
app.use(express.urlencoded({extended:true}));
app.use(express.static(__dirname + '/../build-qmlwasm1-wasm-Debug'));

app.get('/', function(req, res, next) {
	console.log('loading ui');
	res.sendFile(path.join(__dirname + '/../build-qmlwasm1-wasm-Debug/qmlwasm1.html'));
});

app.post('/', function(req, res, next) {
	let command=req.body.command;
	console.log('command:'+command);
	let response = backend.ccall('execute','string',['string'],[command]);
	console.log('response:'+response);
	res.send(response);
});

var port = process.env.PORT || 8080
app.listen(port);
console.log("Listening on port "+port);

//var server = https.createServer({
//	key: fs.readFileSync('key.pem'),
//	cert: fs.readFileSync('cert.pem')
//}, app);

//server.setTimeout(0);
//server.listen(443,function(){process.setuid('r0ller');console.log("Listening on port 443");});
//server.listen(8080,function(){process.setuid('r0ller');console.log("Listening on port 8080");});
