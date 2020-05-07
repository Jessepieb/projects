class Ball {
    constructor(x,y,radius,txtId, scene) {
        this.scene = scene;
        this._location = new THREE.Vector2(x,y);
        this.txtId = txtId;
        //this._velocity = new THREE.Vector2(0,0);
        this._radius = radius;
        //this.texture = new THREE.TextureLoader().load('models/textures/Ball' + this.txtId + '.jpg');

        this.geometry = new THREE.SphereBufferGeometry(this._radius, 32, 32);
        this.material = new THREE.MeshBasicMaterial({color:0x000000});
        // this.material = new THREE.MeshBasicMaterial({map:this.texture});

        this.mesh = new THREE.mesh(this.geometry, this.material);
        this.mesh.position.x = x;
        this.mesh.position.y = y;
        this.mesh.position.z = 1;

    }

    // get location(){
    //     return this._location;
    // }
    //
    // set location(newLocation){
    //     this._location = newLocation;
    // }
    //
    // get velocity(){
    //     return this._velocity;
    // }
    //
    // set velocity(newVel){
    //     this._velocity = newVel;
    // }
    //
    // get radius(){
    //     return this._radius;
    // }
    //
    // set radius(newRad){
    //     this._radius = newRad;
    // }
    //
    // Move(){
    //
    // }
    //
    // Collide(otherObj){
    //
    // }
    //
    // updatePos(){
    //
    // }
}