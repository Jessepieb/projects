class Table {
    constructor(width, height, scene) {
        this._widthScale = 1;//(width/1920);
        this._heightScale = (height / 1080);
        this._width = width;
        this._height = height;
        this.scene = scene;
        // this._location = THREE.Vector2(this._width/2, this._height/2);


        this.wallsMesh = new THREE.Group();
        this.pocketsMesh = new THREE.Group();

        this.walls = new Array(4);
        this.pockets = new Array(3);

        for (let row = 0; row < 3; row++) {
            this.pockets[row] = new Array(2);
        }

        this.base = this.createBase();
    }

    createBase() {
        const w = this._widthScale * 50;
        const h = this._heightScale * 30;
        const geometry = new THREE.PlaneGeometry(w, h);
        const material = new THREE.MeshBasicMaterial({color: 'forestgreen'});
        const mesh = new THREE.Mesh(geometry, material);
        mesh.name = "Base";
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

        this.walls[0] = wall1;
        this.walls[1] = wall2;
        this.walls[2] = wall3;
        this.walls[3] = wall4;

        this.wallsMesh.add(wall1.mesh);
        this.wallsMesh.add(wall2.mesh);
        this.wallsMesh.add(wall3.mesh);
        this.wallsMesh.add(wall4.mesh);
        this.wallsMesh.name = "Walls";
        this.scene.add(this.wallsMesh);

    }


    createPockets() {
        for (let i = -1; i < 2; i++) {
            this.pockets[i + 1][0] = (new Pocket((this._width / 79) * i, this._height / 77, 2));
            this.pocketsMesh.add((this.pockets[i + 1][0]).mesh);
            this.pockets[i + 1][1] = (new Pocket((this._width / 79) * i, (this._height / 77) * -1, 2));
            this.pocketsMesh.add((this.pockets[i + 1][1]).mesh);
        }
        this.pocketsMesh.name = "Pockets";
        this.scene.add(this.pocketsMesh);
    }

    initTable() {
        this.createWalls();
        this.createPockets();
    }

    Collide(ball) {
        if (ball.location.y > 11 && ball.velocity.y > 0) {
            const coll = new THREE.Vector2(1., -1.);
            ball.velocity.multiply(coll);
        }
        if (ball.location.y < -11 && ball.velocity.y < 0) {
            const coll = new THREE.Vector2(1., -1.);
            ball.velocity.multiply(coll);
        }

        if (ball.location.x > 24 && ball.velocity.x > 0) {
            const coll = new THREE.Vector2(-1., 1.);
            ball.velocity.multiply(coll);
        }
        if (ball.location.x < -23 && ball.velocity.x < 0) {
            const coll = new THREE.Vector2(-1., 1.);
            ball.velocity.multiply(coll);
        }

    }
}