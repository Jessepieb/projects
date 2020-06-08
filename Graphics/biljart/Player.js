class Player {
    constructor(name,playerTurn) {
        this.isOdd = null;
        this._score = 0;

        this._name = name;
        this.turn = playerTurn;
    }

    get score(){
        return this._score;
    }

    set score(newScore){
        this._score = newScore;
    }

    get name(){
        return this._name;
    }
}