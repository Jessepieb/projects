class Table {
    constructor(width, height, scene) {
        this._widthScale = 1;//(width/1920);
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
        var w = this._widthScale * 2;
        var l = this._heightScale * 56;
        // this.walls.add(new Wall(this._height/2,this._width/2,w,l));\
        const wall1 = new Wall(0,this._height/75,l,w);
        const wall2 = new Wall(0,(this._height/75)*-1,l,w);

        w = this._widthScale * 2;
        l = this._heightScale* 31;

        const wall3 = new Wall((this._width/75)*-1,0,w,l);
        const wall4 = new Wall(this._width/75,0,w,l);
        //wall.location = new THREE.Vector2(0, (this._height/75));
        this.scene.add(wall1.mesh);
        this.scene.add(wall2.mesh);
        this.scene.add(wall3.mesh);
        this.scene.add(wall4.mesh);
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