class Wall {
    constructor(x,y,width,depth) {
        this.location = new THREE.Vector2(x,y);
        this.dimensions = {width, depth};

        this._geometry = new THREE.BoxGeometry(this.dimensions.width, this.dimensions.depth,2);
        this._texture = new THREE.TextureLoader().load('models/textures/wood1.jpg');
        this._material = new THREE.MeshBasicMaterial({map:this._texture});

        this.mesh = new THREE.Mesh(this._geometry,this._material);
    }
}