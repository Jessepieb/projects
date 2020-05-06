class Table {
    constructor(width, height) {
        this._width = width;
        this._height = height;
        // this._location = THREE.Vector2(width/2, height/2);
        this.walls = new THREE.Group();
        this.pockets = new THREE.Group();
    }

    createBase(){
        const geometry = new THREE.PlaneGeometry(this._width, this._height);
        const material = new THREE.MeshBasicMaterial({color:0xffffff});

        return material;
    }


    createWalls(x,y,width,depth){
        const wall = new Wall(x,y,width,depth);
        this.walls.add(wall);
    }


    createPockets(){
        const pocket = new Pocket(x, y, radius);
        this.pockets.add(pocket);
    }
}