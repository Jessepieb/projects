class Ball {
    constructor(x, y, radius, txtId, scene) {
        this.scene = scene;
        this._location = new THREE.Vector2(x, y);
        // this.txtId = txtId;
        this._radius = radius;

        this._velocity = new THREE.Vector2(0, 0);

        // this.texture = new THREE.TextureLoader().load('models/textures/Ball' + this.txtId + '.jpg');

        this.geometry = new THREE.SphereGeometry(this._radius, 32, 32);
        this.material = new THREE.MeshBasicMaterial({color: "white"});
        // this.material = new THREE.MeshBasicMaterial({map:this.texture});

        this.mesh = new THREE.Mesh(this.geometry, this.material);
        this.mesh.position.x = this._location.x;
        this.mesh.position.y = this._location.y;
        // this.mesh.position.z = 2;

        this.scene.add(this.mesh);
    }

    get location() {
        return this._location;
    }

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