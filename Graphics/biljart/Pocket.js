class Pocket {
    constructor(x,y,radius){
        this._location = new THREE.Vector2(x,y);
        this._radius = radius;

        this._geometry = new THREE.CylinderGeometry(this._radius, this._radius, 2);
        this._material = new THREE.MeshBasicMaterial({color:0x000000});

        this.mesh = new THREE.Mesh(this._geometry, this._material);
    }

    get location(){
        return this._location;
    }

    set location(newLoc){
        this._location = newLoc;
    }

    set radius(newRad){
        this._radius = newRad;
    }

}