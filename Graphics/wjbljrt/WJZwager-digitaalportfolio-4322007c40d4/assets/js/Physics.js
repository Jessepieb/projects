/**
 * Created by Frank Keuning on 11-10-2016.
 */

function newCollide(ball1, ball2)
{
    a = ball1.position.x - ball2.position.x;
    b = ball1.position.z - ball2.position.z;
    ab = Math.sqrt(((a * a) + (b * b)));

    if(ab < 1 && ball1.speed != 0)
    {
        var collisionPointX = (ball1.position.x + ball2.position.x)/2;
        var collisionPointZ = (ball1.position.z + ball2.position.z)/2;

        ball1.directionX = (collisionPointX - ball1.position.x)*-1;
        ball2.directionX = ((collisionPointX - ball2.position.x)*-1)/4;

        ball1.directionZ = (collisionPointZ - ball1.position.z)*-1;
        ball2.directionZ = ((collisionPointZ - ball2.position.z)*-1)/4;
        ball2.speed = ball1.speed;
    }
    else if(ab <1 && ball1.speed == 0)
    {
        ball1.speed = 0.1;
    }
}

function collideWall (Ball1){
    if(Ball1.position.x >= 6.4 || Ball1.position.x <= -6.6)
    {
        Ball1.directionX *= -1;
        if(Ball1.speed == 0 && Ball1.position.x >= 6.4)
        {
            Ball1.position.x -= 0.01;
        }
        if(Ball1.speed == 0 && Ball1.position.x <= -6.6)
        {
            Ball1.position.x += 0.01;
        }
    }

    else if(Ball1.position.z >= 11.6 || Ball1.position.z <= -11.9)
    {
        Ball1.directionZ *= -1;
        if(Ball1.speed == 0 && Ball1.position.z >= 11.6)
        {
            Ball1.position.z -= 0.1;
        }
        if(Ball1.speed == 0 && Ball1.position.z <= -11.9)
        {
            Ball1.position.z += 0.1;
        }
    }
}

function slowDown (Ball){
    if(Ball.speed > 0 || Ball.speed < 0)
    {
        Ball.speed *= 0.97;
    }
    if(Ball.speed >= -0.00005 && Ball.speed <= 0.00005)
    {
        Ball.speed = 0;
    }

}
function scorePoint(ball1) {
    var whiteball = false;
    if ((ball1.position.x > 6.20 && ball1.position.x < 8.54) && (ball1.position.z > 11.27 && ball1.position.z < 13.95)){
        console.log("score 1 ");
        scene.remove(ball1);
        return ball1;
    }
    if ((ball1.position.x > -8.78 && ball1.position.x < -6.38) && (ball1.position.z > 11.47 && ball1.position.z < 13.75)){
        console.log("score 2 ");
        scene.remove(ball1);
        return ball1;
    }
    if ((ball1.position.x > -8.78 && ball1.position.x < -6.38) && (ball1.position.z > -1.2 && ball1.position.z < 1.2)) {
        console.log("score 3 ");
        scene.remove(ball1);
        return ball1;
    }
    if((ball1.position.x > 6.38 && ball1.position.x < 8.78) && (ball1.position.z > -1.2 && ball1.position.z < 1.2)) {
        console.log("score 4 ");
        scene.remove(ball1);
        return ball1;
    }
    if((ball1.position.x > -8.78 && ball1.position.x < -6.38) && (ball1.position.z < -11.47 && ball1.position.z > -13.75)) {
        console.log("score 5 ");
        scene.remove(ball1);
        return ball1;
    }
    if((ball1.position.x > 6.30 && ball1.position.x < 8.34) && (ball1.position.z < -11.47 && ball1.position.z > -13.75)) {
        console.log("score 6 ");
        scene.remove(ball1);
        return ball1;
    }
}