class Ball {
    constructor(x, y, radius, scene, balltype) {
        const limit = 1.3;
        this.minSpeed = new THREE.Vector2(-limit, -limit);
        this.maxSpeed = new THREE.Vector2(limit, limit);
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
        if (this._velocity.x > 0.005 || this._velocity.x < -0.005) {
            this._velocity.x = this._velocity.x * 0.99;
        } else {
            this._velocity.x = 0;
        }

        if (this._velocity.y > 0.005 || this._velocity.y < -0.005) {
            this._velocity.y = this._velocity.y * 0.99;
        } else {
            this._velocity.y = 0;
        }
    }

    applyForce(force) {
        this.velocity = (force);
        // this.velocity.add(force.clamp(this.minSpeed, this.maxSpeed));
    }

    distance(other){
        let dx = other.location.x - this._location.x;
        let dy = other.location.y - this._location.y;
        return Math.sqrt((dx*dx)+(dy*dy));
    }
    checkCollision(otherObj) {
        //const magVect = new THREE.Vector2(otherObj.location).sub(this.location);

        if (otherObj !== undefined) {
            const distance = this.distance(otherObj);
            //const otherDisVectMag = otherObj.mag(this);

            const minDistance = this.radius + otherObj.radius;
            if (distance <= minDistance) {
                let vCollision = new THREE.Vector2(
                    otherObj.location.x - this.location.x,
                    otherObj.location.y - this.location.y);
                let vCollisionNorm = new THREE.Vector2(vCollision.x/distance, vCollision.y/distance);

                let relativeVelocity = new THREE.Vector2(
                    this._velocity.x - otherObj.velocity.x,
                    this._velocity.y - otherObj.velocity.y);

                let speed = relativeVelocity.x * vCollisionNorm.x+relativeVelocity.y*vCollisionNorm.y;
                if (speed > 0) {
                    this._velocity.x = this._velocity.x - (vCollisionNorm.x*speed);
                    this._velocity.y = this._velocity.y - (vCollisionNorm.y*speed);

                    otherObj.velocity.x = otherObj.velocity.x + (vCollisionNorm.x*speed);
                    otherObj.velocity.y = otherObj.velocity.y +(vCollisionNorm.y*speed);

                    // const newValue = this._velocity;
                    // this.velocity = otherObj.velocity;
                    // otherObj.velocity = newValue;
                }
                //this.Move();
                //otherObj.Move();
            }
        }
    }
}