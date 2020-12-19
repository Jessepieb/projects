class Player {
    constructor(name,playerTurn) {
        this._isOdd =-1;
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

    get isOdd(){
        return this._isOdd;
    }

    set isOdd(bool){
        this._isOdd = bool;
    }

    get name(){
        return this._name;
    }
}