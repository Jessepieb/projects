class Table {
    constructor(width, height, scene) {
        this._widthScale = 1;//(width/1920);
        this._heightScale = (height / 1080);
        this._width = width;
        this._height = height;
        this.scene = scene;
        // this._location = THREE.Vector2(this._width/2, this._height/2);

        this.walls = new THREE.Group();
        this.pockets = new THREE.Group();
        this.base = this.createBase();
    }

    createBase() {
        const w = this._widthScale * 50;
        const h = this._heightScale * 30;
        const geometry = new THREE.PlaneGeometry(w, h);
        const material = new THREE.MeshBasicMaterial({color: 'forestgreen'});
        const mesh = new THREE.Mesh(geometry, material);
        this.scene.add(mesh);
        this.initTable();

        return mesh;
    }


    createWalls() {
        var w = this._widthScale * 2.35;
        var l = this._heightScale * 60;
        const wall1 = new Wall(0, this._height / 73, l, w);
        const wall2 = new Wall(0, (this._height / 73) * -1, l, w);

        l = this._heightScale * 27;

        const wall3 = new Wall((this._width / 75) * -1, 0, w, l);
        const wall4 = new Wall(this._width / 75, 0, w, l);

        this.walls.add(wall1.mesh);
        this.walls.add(wall2.mesh);
        this.walls.add(wall3.mesh);
        this.walls.add(wall4.mesh);
        this.scene.add(this.walls);

    }


    createPockets() {
        for (let i = -1; i < 2; i++) {
            var pocket = new Pocket((this._width / 78) * i, this._height / 77, 2);
            this.pockets.add(pocket.mesh);
            pocket = new Pocket((this._width / 78) * i, (this._height / 77) * -1, 2);
            this.pockets.add(pocket.mesh)
        }
        this.scene.add(this.pockets);
    }

    initTable() {
        this.createWalls();
        this.createPockets();
    }
}