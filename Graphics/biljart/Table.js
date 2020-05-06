class Table {
    constructor(width, height) {
        this._width = width;
        this._height = height;
        // this._location = THREE.Vector2(width/2, height/2);

    }

    createBase(){
        const geometry = new THREE.PlaneGeometry(this._width, this._height);
        const material = new THREE.MeshBasicMaterial({color:0xffffff});

        return material;
    }


    createWalls(){

    }


    createPockets(){

    }
}