class Pocket {
    constructor(x, y, radius) {
        this._location = new THREE.Vector2(x, y);
        this._radius = radius;

        this._geometry = new THREE.CylinderGeometry(this._radius, this._radius, 2, 32);
        this._material = new THREE.MeshBasicMaterial({color: 0x000000});

        this.mesh = new THREE.Mesh(this._geometry, this._material);
        this.mesh.rotateX(1.5);
        this.mesh.position.x = this._location.x;
        this.mesh.position.y = this._location.y;

        this.mesh.name = "Pocket";
    }

    get location() {
        return this._location;
    }

    set location(newLoc) {
        this._location = newLoc;
        this.mesh.position.x = this._location.x;
        this.mesh.position.y = this._location.y;
    }

    set radius(newRad) {
        this._radius = newRad;
    }

    Collide(ball, arrayLength, player) {
        if (this.location.distanceTo(ball.location) < (this._radius + ball.radius)) {
            switch (ball.balltype) {
                case ("black"):
                    if (arrayLength > 2) {
                        console.log("Game Over!")
                    } else {
                        console.log("Current player wins");
                    }
                    break;

                case ("even"):
                    if (player.isOdd){

                    }
                return true;

                case("odd"):
                    if (player.isOdd){
                        player.score = player.score+1;
                    }
                    return true;
                default:
                    ball.velocity = new THREE.Vector2(0, 0);
                    ball.location = new THREE.Vector2(14, 0);
            }
            console.log("Ball sunk " + ball.balltype);
        }
    }

}