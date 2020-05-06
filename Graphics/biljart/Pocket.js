class Pocket {
    constructor(x,y,radius){
        this._x = x;
        this._y = y;
        this._radius = radius;

        this._geometry = new THREE.CylinderGeometry(this._radius, this._radius, 2);
        this._material = new THREE.MeshBasicMaterial({color:0x000000});
        this._mesh = new THREE.Mesh(geometry, material);
    }

}