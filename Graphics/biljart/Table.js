class Table {
    constructor(width, height, scene) {
        this._widthScale = (width/1920);
        this._heightScale = (height/1080);
        this._width = width;
        this._height = height;
        this.scene = scene;
        //this._location = THREE.Vector2(this._width/2, this._height/2);

        this.walls = new THREE.Group();
        this.pockets = new THREE.Group();
        this.base = this.createBase();
    }

    createBase(){
        const w = this._widthScale * 52;
        const h = this._heightScale * 30;
        const geometry = new THREE.PlaneGeometry(w, h);
        const material = new THREE.MeshBasicMaterial({color:0x009900});
        this.scene.add(new THREE.Mesh(geometry, material));
        this.initTable();
    }


    createWalls(){
        const w = this._widthScale * 2;
        const l = this._heightScale * 44;
        // this.walls.add(new Wall(this._height/2,this._width/2,w,l));\
        const wall = new Wall(this._height,this._width,l,w);
        //wall.location = new THREE.Vector2(this._height/2, this._width/2);
        // wall.location(new THREE.Vector2(this._width,this._height/2));
        this.scene.add(wall.mesh);
        // const wall = new Wall(x,y,width,depth);
        // this.walls.add(wall);
    }

    //
    // createPockets(){
    //     let xoffset = this._width/3
    //     for(let i = -1; i < this._width;) {
    //         const pocket = new Pocket(x, y, radius);
    //         this.pockets.add(pocket);
    //     }
    // }

    initTable(){
        this.createWalls();
        scene.add(this.walls);
        //this.createPockets();
    }
}