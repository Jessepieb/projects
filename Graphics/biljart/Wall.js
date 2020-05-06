class Wall {
    constructor(x,y,width,depth) {
        this._location = new THREE.Vector2(x,y);
        this._dimensions = {width, depth};

        this._geometry = new THREE.BoxGeometry(this.dimensions.width, this.dimensions.depth,2);
        this._texture = new THREE.TextureLoader().load('models/textures/wood1.jpg');
        this._material = new THREE.MeshBasicMaterial({map:this._texture});

        this.mesh = new THREE.Mesh(this._geometry,this._material);
    }

    get location(){
        return this._location;
    }

    set location(newLoc){
        this._location = newLoc;
    }

    get dimensions(){
        return this._dimensions;
    }

    set dimensions(newDim){
        this._dimensions = newDim;
    }
}