/**
 * Created by Frank on 29-9-2016.
 */

var geometry = new THREE.SphereGeometry(0.5,32,32);
var blackMaterial = new THREE.MeshPhongMaterial({color: 0x000000});
var blackSphere = new THREE.Mesh( geometry, blackMaterial );

Object.defineProperty(blackSphere, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(blackSphere, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(blackSphere, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

//Whiteball

var material = new THREE.MeshPhongMaterial( {color: 0xffffff} );
var whiteSphere = new THREE.Mesh( geometry, material );
Object.defineProperty(whiteSphere, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(whiteSphere, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(whiteSphere, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

//yellow material
var yellowMaterial = new THREE.MeshPhongMaterial( {color: 0xffff00} );


//purpleball

var purpleMaterial = new THREE.MeshPhongMaterial( {color: 0xae22bf} );
var purpleSphere1 = new THREE.Mesh( geometry, purpleMaterial );

Object.defineProperty(purpleSphere1, 'directionX', {
   value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere1, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere1, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});


var yellowSphere1 = new THREE.Mesh( geometry, yellowMaterial);

Object.defineProperty(yellowSphere1, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere1, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere1, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});



var yellowSphere2 = new THREE.Mesh( geometry, yellowMaterial );

Object.defineProperty(yellowSphere2, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere2, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere2, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});


var purpleSphere2 = new THREE.Mesh( geometry, purpleMaterial );

Object.defineProperty(purpleSphere2, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere2, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere2, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

var purpleSphere3 = new THREE.Mesh( geometry, purpleMaterial );

Object.defineProperty(purpleSphere3, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere3, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere3, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

var yellowSphere3 = new THREE.Mesh( geometry, yellowMaterial );

Object.defineProperty(yellowSphere3, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere3, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere3, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

var purpleSphere4 = new THREE.Mesh( geometry, purpleMaterial );

Object.defineProperty(purpleSphere4, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere4, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere4, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

var yellowSphere4 = new THREE.Mesh( geometry, yellowMaterial );

Object.defineProperty(yellowSphere4, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere4, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere4, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

var purpleSphere5 = new THREE.Mesh( geometry, purpleMaterial );

Object.defineProperty(purpleSphere5, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere5, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere5, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

var yellowSphere5 = new THREE.Mesh( geometry, yellowMaterial );

Object.defineProperty(yellowSphere5, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere5, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere5, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

var purpleSphere6 = new THREE.Mesh( geometry,purpleMaterial );

Object.defineProperty(purpleSphere6, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere6, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere6, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

var yellowSphere6 = new THREE.Mesh( geometry, yellowMaterial );

Object.defineProperty(yellowSphere6, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere6, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere6, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

var purpleSphere7 = new THREE.Mesh( geometry, purpleMaterial);

Object.defineProperty(purpleSphere7, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere7, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(purpleSphere7, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

var yellowSphere7 = new THREE.Mesh( geometry, yellowMaterial );

Object.defineProperty(yellowSphere7, 'directionX', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere7, 'directionZ', {
    value: 0,
    writable: true,
    configurable: true
});

Object.defineProperty(yellowSphere7, 'speed', {
    value: 0,
    writable: true,
    configurable: true
});

