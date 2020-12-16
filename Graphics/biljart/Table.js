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
        this.initTable();
    }

    createBase() {
        const w = this._widthScale * 50;
        const h = this._heightScale * 30;
        const geometry = new THREE.PlaneGeometry(w, h);
        const material = new THREE.MeshBasicMaterial({color: 0x33cc33});
        const mesh = new THREE.Mesh(geometry, material);
        mesh.name = "Base";
        this.scene.add(mesh);
        return [w,h];
        //return mesh;
    }


    createWalls() {
        var w = this._widthScale * 2.35;
        var l = this._heightScale * 60;
        var wall = new Wall(0, this._height / 73, l, w);
        this.walls.push(wall);
        this.wallsMesh.add(wall.mesh);
        wall = new Wall(0, (this._height / 73) * -1, l, w);
        this.walls.push(wall);
        this.wallsMesh.add(wall.mesh);

        l = this._heightScale * 27;

        wall = new Wall((-this._width / 75), 0, w+.25, l);
        this.walls.push(wall);
        this.wallsMesh.add(wall.mesh);
        wall = new Wall(this._width / 75, 0, w+.25, l);
        this.walls.push(wall);
        this.wallsMesh.add(wall.mesh);

        this.wallsMesh.name = "Walls";
        this.scene.add(this.wallsMesh);

    }


    createPockets() {
        const w = this._width/77;
        const h = this._height/77;
        for (let i = -1; i < 2; i++) {
            this.pockets[i + 1][0] = (new Pocket(w * i, h, 1.75));
            this.pocketsMesh.add((this.pockets[i + 1][0]).mesh);
            this.pockets[i + 1][1] = (new Pocket(w * i, h * -1, 1.75));
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
        if (ball.location.y > (this.base[1]/2) - ball.radius&& ball.velocity.y > 0) {
            ball.velocity.multiply(new THREE.Vector2(1., -1.));
        }
        if (ball.location.y < (-this.base[1]/2) + ball.radius && ball.velocity.y < 0) {
            ball.velocity.multiply(new THREE.Vector2(1., -1.));
        }

        if (ball.location.x > (this.base[0]/2)-ball.radius && ball.velocity.x > 0) {
            ball.velocity.multiply(new THREE.Vector2(-1., 1.));
        }
        if (ball.location.x < (-this.base[0]/2)+ball.radius && ball.velocity.x < 0) {
            ball.velocity.multiply(new THREE.Vector2(-1., 1.));
        }

    }
}