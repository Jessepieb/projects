class Que{
    constructor(x,y, scene) {
        this._scene = scene;
        this._location = new THREE.Vector2(x,y);


        this._material = new THREE.MeshBasicMaterial({color:'red'});
        this.geometry = new THREE.SphereBufferGeometry(0.5,32,32);

        this.mesh = new THREE.Mesh(this.geometry,this._material);
        this.mesh.name = "Que";
        this._scene.add(this.mesh);
    }
    updatepos(){
        this.mesh.position.x = this._location.x;
        this.mesh.position.y = this._location.y;
    }
    set location(newLoc){
        this._location = newLoc;
        this.updatepos();
    }
}