class Que{
    constructor(ball, scene) {
        this._scene = scene;
        this._location = new THREE.Vector2(ball.location.x,ball.location.y);
        this.ball = ball;



        this.material = new THREE.MeshBasicMaterial({color:'red'});
        this.points = [];
        this.points.push( new THREE.Vector2( this.location.x, this.location.y ));
        this.points.push( new THREE.Vector2( this.location.x-ball.radius*2, this.location.y ) );
        this.geometry = new THREE.BufferGeometry().setFromPoints( this.points );
        this.line = new THREE.Line(this.geometry, this.material);

        this.line.name = "Que";
        this.line.z = 1;
        this._scene.add(this.line);
    }

    set location(newLoc){
        this._scene.remove(this.line);
        this.points = [];
        this.points.push( new THREE.Vector2( balls[0].location.x, balls[0].location.y ));
        this.points.push( new THREE.Vector2(balls[0].location.x + (newLoc.x),balls[0].location.y+ (newLoc.y)));
        this.geometry = new THREE.BufferGeometry().setFromPoints( this.points );
        this.line = new THREE.Line(this.geometry, this.material);
        this.line.position.z = 1;
        scene.add(this.line);
    }
    get location(){
        return this._location;
    }
}