class Pocket {
    constructor(x, y, radius) {
        this._location = new THREE.Vector2(x, y);
        this._radius = radius;

        this._geometry = new THREE.CylinderGeometry(this._radius, this._radius, .25, 32);
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

    applyColour(player,otherPlayer){
        switch (player.isOdd){
            case 0:
                document.getElementById("EvenColor").innerText= player.name;
                document.getElementById("OddColor").innerText= otherPlayer.name;
                break;
            case 1:
                document.getElementById("EvenColor").innerHTML= otherPlayer.name;
                document.getElementById("OddColor").innerText= player.name;
                break;

        }

    }

    static checkIsMoving(){
        let isMoving = false;
        for(let i = 0; i<balls.length; i++) {
            if (balls[i] !== undefined) {
                if (balls[i].velocity.x !== 0 || balls[i].velocity.y !== 0) {
                    isMoving = true;
                }
            }
        }
        return isMoving;
    }


    Collide(ball, arrayLength, player, otherPlayer) {
        if (this.location.distanceTo(ball.location) < (this._radius*.75 + ball.radius)) {
            if (player.isOdd === -1){
                if(ball.balltype === "even"){
                    player.isOdd = 0;
                    otherPlayer.isOdd = 1;
                    this.applyColour(player,otherPlayer);
                }
                else if (ball.balltype === "odd"){
                    player.isOdd = 1;
                    otherPlayer.isOdd = 0;
                    this.applyColour(player,otherPlayer);
                }
            }
            switch (ball.balltype) {
                case ("black"):
                    if (player.score === 7) {
                        document.getElementById("WinText").innerHTML=("Game Over! " + player.name + " Wins!")
                    } else {
                        document.getElementById("WinText").innerHTML=("Black Ball! " + otherPlayer.name +" wins");
                    }
                   return true;

                case ("even"):
                    if (player.isOdd){
                        otherPlayer.score = otherPlayer.score+ 1;
                    }
                    else{
                        player.score = player.score + 1;
                        scored=true;
                    }
                return true;

                case("odd"):
                    if (player.isOdd){
                        player.score = player.score + 1;
                        scored=true;
                    }
                    else{
                        otherPlayer.score = otherPlayer.score+ 1;
                    }
                    return true;
                default:
                    ball.velocity = new THREE.Vector2(0, 0);
                    ball.location = new THREE.Vector2(14, 0);
                    scored=false;
                    return false;
            }

        }
    }

}