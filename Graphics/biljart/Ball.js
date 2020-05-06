class Ball {
    constructor(x,y,radius,txtId) {
        this._location = new THREE.Vector2(x,y);
        this._velocity = new THREE.Vector2(0,0);
        this._radius = radius;
        this.texture = new THREE.TextureLoader().load('models/textures/Ball' + txtId + '.jpg');

        this.geometry = new THREE.SphereBufferGeometry(this._radius, 32, 32);
        this.material = new THREE.MeshBasicMaterial({map:this.texture});

        this.mesh = new THREE.mesh(this.geometry, this.material);
    }

    get location(){
        return this._location;
    }

    set location(newLocation){
        this._location = newLocation;
    }

    get velocity(){
        return this._velocity;
    }

    set velocity(newVel){
        this._velocity = newVel;
    }

    get radius(){
        return this._radius;
    }

    set radius(newRad){
        this._radius = newRad;
    }

    Move(){

    }

    Collide(otherObj){

    }

    updatePos(){

    }
}