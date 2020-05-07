class Wall {
    constructor(x,y,width,depth) {
        this._location = new THREE.Vector2(x,y);
        this._dimensions = {width, depth};

        this._geometry = new THREE.BoxGeometry(this.dimensions.width, this.dimensions.depth,3);
        this._texture = new THREE.TextureLoader().load('models/textures/wood1.jpg');
        this._material = new THREE.MeshBasicMaterial({map:this._texture});

        this.mesh = new THREE.Mesh(this._geometry,this._material);

        this.location = this._location;
    }

    get location(){
        return this._location;
    }

    set location(newLoc){
        this._location = newLoc;
        this.mesh.position.x = this._location.x;
        this.mesh.position.y = this._location.y;
    }

    get dimensions(){
        return this._dimensions;
    }

    set dimensions(newDim){
        this._dimensions = newDim;
    }
}