class Ball {
    constructor(x, y, radius, scene) {
        this._location = new THREE.Vector2(x, y);
        this.scene = scene;
        this._radius = radius;
        this._velocity = new THREE.Vector2(0, 0);

        this.texture = new THREE.TextureLoader().load('models/textures/Ball2.jpg');

        this.geometry = new THREE.SphereBufferGeometry(this._radius, 32, 32);
        // this.material = new THREE.MeshBasicMaterial({color: 0xffff00});
        this.material = new THREE.MeshBasicMaterial({map: this.texture});

        this.mesh = new THREE.Mesh(this.geometry, this.material);
        //this.updateLoc();
        this.location = this._location;
        this.mesh.position.z = 1;
        this.mesh.name = "Ball";
        this.scene.add(this.mesh);
    }

    get location() {
        return this._location;
    }

    set location(newLocation) {
        this._location = newLocation;
        this.mesh.position.x = this._location.x;
        this.mesh.position.y = this._location.y;
    }

    static Collide(otherObj) {

    }

    get velocity() {
        return this._velocity;
    }

    set velocity(newVel) {
        this._velocity = newVel;
    }

    get radius() {
        return this._radius;
    }

    Move() {
        this.location = this._location.add(this._velocity);
        if (this._velocity.x > 0.002 || this._velocity.x < -0.002) {
            this._velocity.x = this._velocity.x * 0.995;
        } else {
            this._velocity.x = 0;
        }

        if (this._velocity.y > 0.001 || this._velocity.y < -0.001) {
            this._velocity.y = this._velocity.y * 0.995;
        } else {
            this._velocity.y = 0;
        }
    }

    applyForce(force) {
        this._velocity.add(force);
    }

    //
    Collide(otherObj) {
        if (this.location.distanceTo(otherObj.location) < (this._radius + otherObj.radius)) {
            var newValue = this._velocity;

            this.applyForce(otherObj.velocity);
            otherObj.applyForce(newValue);
            this._velocity.multiply(new THREE.Vector2(-1., -1.));
        }
    }

}