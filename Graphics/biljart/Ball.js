class Ball {
    constructor(x, y, radius, scene, balltype) {

        this.minSpeed = new THREE.Vector2(-0.2, -0.2);
        this.maxSpeed = new THREE.Vector2(0.2, 0.2);
        this.scene = scene;

        this._location = new THREE.Vector2(x, y);
        this._radius = radius;
        this._velocity = new THREE.Vector2(0, 0);

        this._balltype = balltype;

        //this._velocity.clamp(0,0.006);

        switch (this._balltype) {
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

    get balltype() {
        return this._balltype;
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
        this._velocity = newVel.clamp(this.minSpeed, this.maxSpeed);
    }

    get radius() {
        return this._radius;
    }

    Move() {
        this.velocity = this._velocity.clamp(this.minSpeed, this.maxSpeed);
        this.location = this._location.add(this._velocity);
        if (this._velocity.x > 0.001 || this._velocity.x < -0.001) {
            this._velocity.x = this._velocity.x * 0.992;
        } else {
            this._velocity.x = 0;
        }

        if (this._velocity.y > 0.001 || this._velocity.y < -0.001) {
            this._velocity.y = this._velocity.y * 0.992;
        } else {
            this._velocity.y = 0;
        }
    }

    applyForce(force) {
        this.velocity.add(force);
        // this.velocity.add(force.clamp(this.minSpeed, this.maxSpeed));
    }

    dis(other){
        let dx = this._location.x - other.location.x;
        let dy = this._location.y - other.location.y;
        return Math.sqrt((dx*dx)+(dy*dy));
    }
    checkCollision(otherObj) {
        const disVect = new THREE.Vector2(otherObj.location).sub(this.location);
        const disVectMag = otherObj.dis(this);

        const minDistance = this.radius + otherObj.radius
        if (disVectMag <= minDistance) {
            if(this.balltype === undefined){
                console.log("collided with "+ otherObj.balltype)
            }
            var newValue = this._velocity;
            this.velocity= otherObj.velocity;
            otherObj.velocity = newValue;

            this.Move();
            otherObj.Move();
        }
    }

}