class Que{
    constructor(x,y, scene) {
        this._scene = scene;
        this._location = new THREE.Vector2(x,y);

        this.points = [];
        this.points.push( new THREE.Vector2(this._location.x, this._location.y) );
        this.points.push( new THREE.Vector2( 10, 0) );


        this._material = new THREE.LineBasicMaterial({color:'red'});
        this.geometry = new THREE.BufferGeometry().setFromPoints(this.points);

        this.geometry.verticesNeedUpdate = true;

        this.mesh = new THREE.Line(this.geometry,this._material);

        this._scene.add(this.mesh);
    }

    set location(newLoc){
        this._location = newLoc;
    }

    update(){

    }


}