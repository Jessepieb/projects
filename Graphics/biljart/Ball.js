class Ball {
    constructor(x, y, radius, scene, ballsort) {

        this.minSpeed = new THREE.Vector2(-0.2, -0.2);
        this.maxSpeed = new THREE.Vector2(0.2, 0.2);
        this.scene = scene;

        this._location = new THREE.Vector2(x, y);
        this._radius = radius;
        this._velocity = new THREE.Vector2(0, 0);

        this._ballsort = ballsort;

        //this._velocity.clamp(0,0.006);

        switch (this._ballsort) {
            case("black"):
                this.material = new THREE.MeshBasicMaterial({color: 0x000000});
                break;
            case("odd"):
                this.material = new THREE.MeshBasicMaterial({color: 0x0000ff});
                break;
            case("even"):
                this.material = new THREE.MeshBasicMaterial({color: 0xff0000});
                break;
            default:
                this.material = new THREE.MeshBasicMaterial({color: 0xffffff});

        }
        // this.texture = new THREE.TextureLoader().load('models/textures/Ball2.jpg');
        //this.material = new THREE.MeshBasicMaterial({map: this.texture});


        this.geometry = new THREE.SphereBufferGeometry(this._radius, 32, 32);
        this.mesh = new THREE.Mesh(this.geometry, this.material);


        this.location = this._location;
        this.mesh.position.z = 1;
        this.mesh.name = "Ball";
        this.scene.add(this.mesh);
    }

    get ballsort() {
        return this._ballsort;
    }

    get location() {
        return this._location;
    }

    set location(newLocation) {
        this._location = newLocation;
        this.mesh.position.x = this._location.x;
        this.mesh.position.y = this._location.y;
    }

    get velocity() {
        return this._velocity;
    }

    set velocity(newVel) {
        var corrected = newVel.clamp(this.minSpeed, this.maxSpeed);
        this._velocity = corrected;
    }

    get radius() {
        return this._radius;
    }

    Move() {
        this.velocity = this._velocity.clamp(this.minSpeed, this.maxSpeed);
        this.location = this._location.add(this._velocity);
        if (this._velocity.x > 0.001 || this._velocity.x < -0.001) {
            this._velocity.x = this._velocity.x * 0.985;
        } else {
            this._velocity.x = 0;
        }

        if (this._velocity.y > 0.001 || this._velocity.y < -0.001) {
            this._velocity.y = this._velocity.y * 0.985;
        } else {
            this._velocity.y = 0;
        }
    }

    applyForce(force) {
        this.velocity.add(force);
        // this.velocity = this.velocity.clamp(this.minSpeed, this.maxSpeed);
    }

    //
    Collide(otherObj) {
        if (this.location.distanceTo(otherObj.location) < (this._radius + otherObj.radius)) {
            var newValue = this._velocity;
            var newOtherValue = otherObj.velocity;


            this.applyForce(newOtherValue);
            otherObj.applyForce(newValue);

            // this._velocity.multiply(new THREE.Vector2(-0.9, -0.9));
            this._velocity.multiplyScalar(-0.985);
        }
    }

}