const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
canvas.width = 800;
canvas.height = 600;

let circles = [
    {x: 200, y: 300, r: 0},
    {x: 400, y: 150, r: 0},
    {x: 600, y: 400, r: 0}
];

const start = {x: 50, y: 50};
const target = {x: 750, y: 550};
let player = {...start};

const radiusIncreaseRate = 1; // 1 unit per second
const playerSpeed = 1; // 1 unit per second

let keys = {};

function drawCircle(circle) {
    ctx.beginPath();
    ctx.arc(circle.x, circle.y, circle.r, 0, Math.PI * 2);
    ctx.strokeStyle = 'red';
    ctx.stroke();
}

function drawPlayer() {
    ctx.beginPath();
    ctx.arc(player.x, player.y, 5, 0, Math.PI * 2);
    ctx.fillStyle = 'green';
    ctx.fill();
}

function drawTarget() {
    ctx.beginPath();
    ctx.arc(target.x, target.y, 5, 0, Math.PI * 2);
    ctx.fillStyle = 'blue';
    ctx.fill();
}

function updateCircles(deltaTime) {
    for (let circle of circles) {
        circle.r += radiusIncreaseRate * deltaTime;
    }
}

function movePlayer(deltaTime) {
    if (keys['ArrowUp']) player.y -= playerSpeed * deltaTime;
    if (keys['ArrowDown']) player.y += playerSpeed * deltaTime;
    if (keys['ArrowLeft']) player.x -= playerSpeed * deltaTime;
    if (keys['ArrowRight']) player.x += playerSpeed * deltaTime;
}

function checkCollision() {
    for (let circle of circles) {
        const dist = Math.hypot(circle.x - player.x, circle.y - player.y);
        if (dist <= circle.r + 5) {
            alert("You hit a circle! Game over.");
            resetGame();
        }
    }
    const targetDist = Math.hypot(target.x - player.x, target.y - player.y);
    if (targetDist <= 5) {
        alert("You reached the target! Victory!");
        resetGame();
    }
}

function resetGame() {
    player = {...start};
    circles.forEach(circle => circle.r = 0);
}

function gameLoop(timestamp) {
    const deltaTime = 0.016; // assuming 60 FPS

    ctx.clearRect(0, 0, canvas.width, canvas.height);

    updateCircles(deltaTime);
    movePlayer(deltaTime);
    drawTarget();
    drawPlayer();
    for (let circle of circles) {
        drawCircle(circle);
    }

    checkCollision();

    requestAnimationFrame(gameLoop);
}

document.addEventListener('keydown', (e) => {
    keys[e.key] = true;
});

document.addEventListener('keyup', (e) => {
    keys[e.key] = false;
});

requestAnimationFrame(gameLoop);

