class Table {
    constructor(width, height, scene) {
        this._width = (width/1920)*52;
        this._height = (height/1080)*30;
        this._location = THREE.Vector2(this._width/2, this._height/2);

        this.base = this.createBase();
        this.walls = new THREE.Group();
        this.pockets = new THREE.Group();


    }

    createBase(){
        const geometry = new THREE.PlaneGeometry(this._width, this._height);
        const material = new THREE.MeshBasicMaterial({color:0x009900});
        scene.add(new THREE.Mesh(geometry, material));
    }


    createWalls(){
        const wall = new Wall(x,y,width,depth);
        this.walls.add(wall);
    }


    createPockets(){
        let xoffset = this._width/3
        for(let i = -1; i < this._width;) {
            const pocket = new Pocket(x, y, radius);
            this.pockets.add(pocket);
        }
    }

    initTable(){
        this.createWalls();
        this.createPockets();
    }
}