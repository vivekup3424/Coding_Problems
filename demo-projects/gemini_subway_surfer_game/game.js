import * as THREE from 'three';
// Make sure you ran: npm install three
// Run with a dev server like: npx vite OR use VS Code Live Server

// Optional: import { OrbitControls } from 'three/addons/controls/OrbitControls.js'; // Uncomment if needed for debugging
// Note: The path 'three/examples/jsm/...' assumes your dev server/build tool
// can resolve paths relative to the 'three' package installed in node_modules.

console.log("game.js starting...");

// --- Basic Setup ---
const scene = new THREE.Scene();
scene.background = new THREE.Color(0x87CEEB); // Sky blue background
scene.fog = new THREE.Fog(0x87CEEB, 15, 60); // Add fog for distance effect (adjusted distances)

const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
// Camera position slightly higher and further back for a better Temple Run feel
camera.position.set(0, 4, 8);
camera.lookAt(0, 1, 0); // Look slightly down towards the path ahead

const renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.shadowMap.enabled = true; // Enable shadows
renderer.shadowMap.type = THREE.PCFSoftShadowMap; // Softer shadows
document.body.appendChild(renderer.domElement); // Append canvas to the body
console.log("Renderer created and canvas added.");

// Optional: Orbit Controls for debugging camera movement (uncomment related lines if using)
// const controls = new OrbitControls(camera, renderer.domElement);
// controls.target.set(0, 1, 0); // Point controls towards the player area

// --- Lighting ---
const ambientLight = new THREE.AmbientLight(0xffffff, 0.7); // Soft white light
scene.add(ambientLight);

const directionalLight = new THREE.DirectionalLight(0xffffff, 0.9);
directionalLight.position.set(8, 15, 10); // Position light source
directionalLight.castShadow = true;
// Configure shadow properties
directionalLight.shadow.mapSize.width = 2048; // Higher resolution for better shadows
directionalLight.shadow.mapSize.height = 2048;
directionalLight.shadow.camera.near = 0.5;
directionalLight.shadow.camera.far = 50;
// Adjust shadow camera bounds to focus on the play area
directionalLight.shadow.camera.left = -10;
directionalLight.shadow.camera.right = 10;
directionalLight.shadow.camera.top = 10;
directionalLight.shadow.camera.bottom = -10;
scene.add(directionalLight);
// Optional: visualize the shadow camera
// const shadowHelper = new THREE.CameraHelper(directionalLight.shadow.camera);
// scene.add(shadowHelper);


// --- Game Elements (Placeholders) ---

// Player (simple cube for now)
const playerHeight = 1.5;
const playerGeometry = new THREE.BoxGeometry(0.8, playerHeight, 0.8); // Slimmer player
const playerMaterial = new THREE.MeshStandardMaterial({ color: 0xff4500 }); // Orange-Red
const player = new THREE.Mesh(playerGeometry, playerMaterial);
player.castShadow = true;
player.position.y = playerHeight / 2; // Place its bottom on the ground (y=0)
scene.add(player);
// Keep light target updated to player position
directionalLight.target = player;


// Ground / Path (simple plane for now)
const pathSegments = [];
const segmentLength = 20; // Longer path segments
const segmentWidth = 4;   // Slightly wider path
const numInitialSegments = 8; // More segments visible initially
let lastSegmentZ = 0;

function createPathSegment(zPosition) {
    const planeGeometry = new THREE.PlaneGeometry(segmentWidth, segmentLength);
    // Simple texture variation (example)
    const color = Math.random() > 0.5 ? 0x999999 : 0x888888;
    const planeMaterial = new THREE.MeshStandardMaterial({
        color: color, // Varying Grey
        side: THREE.DoubleSide // Render both sides (though only top visible)
    });
    const path = new THREE.Mesh(planeGeometry, planeMaterial);
    path.rotation.x = -Math.PI / 2; // Rotate to be flat
    path.position.y = 0;
    path.position.z = zPosition;
    path.receiveShadow = true; // Allow path to receive shadows
    scene.add(path);
    pathSegments.push(path);
    lastSegmentZ = zPosition; // Track the Z position of the last segment added
    return path;
}

// Initial path segments (place them going into the distance)
for (let i = 0; i < numInitialSegments; i++) {
    createPathSegment(i * -segmentLength + segmentLength / 2);
}

// Obstacles (simple cubes for now)
const obstacles = [];
const obstacleSpawnZ = -30; // How far ahead to attempt spawning obstacles

function createObstacle(lane, zPosition) {
    const obsHeight = 1;
    const obsGeometry = new THREE.BoxGeometry(0.9, obsHeight, 0.9); // Make obstacles slightly wider than player lane gap
    const obsMaterial = new THREE.MeshStandardMaterial({ color: 0x555555 }); // Dark grey
    const obstacle = new THREE.Mesh(obsGeometry, obsMaterial);
    obstacle.castShadow = true;
    obstacle.position.y = obsHeight / 2; // Sit on the ground
    // Lane positions (-1, 0, 1 relative to center) mapped to X coordinates
    const laneXOffset = (lane - 1) * (segmentWidth / 3); // lane 0=left, 1=middle, 2=right
    obstacle.position.x = laneXOffset;
    obstacle.position.z = zPosition;
    scene.add(obstacle);
    obstacles.push(obstacle); // Add to array for tracking/collision
    return obstacle;
}

// --- Game Logic Variables ---
let score = 0;
let gameSpeed = 0.15; // Initial speed
const maxGameSpeed = 0.4; // Maximum speed limit
const speedIncrement = 0.0001; // How much speed increases per frame
let playerLane = 1; // 0=left, 1=middle, 2=right
let isJumping = false;
let jumpVelocity = 0;
const gravity = 0.018; // Slightly stronger gravity
const jumpInitialVelocity = 0.45; // Slightly higher jump
let isGameOver = false;
let targetPlayerX = 0; // Target X position for smooth lane change

// DOM Elements
const scoreElement = document.getElementById('score');
const gameOverElement = document.getElementById('game-over');
const finalScoreElement = document.getElementById('final-score');

// --- Player Controls ---
document.addEventListener('keydown', (event) => {
    if (isGameOver) return; // Don't allow input if game over

    switch (event.key) {
        case 'ArrowLeft': // Move Left
        case 'a':
            if (playerLane > 0) playerLane--;
            break;
        case 'ArrowRight': // Move Right
        case 'd':
            if (playerLane < 2) playerLane++;
            break;
        case 'ArrowUp': // Jump
        case 'w':
        case ' ': // Space bar
            if (!isJumping) {
                isJumping = true;
                jumpVelocity = jumpInitialVelocity;
                // Add visual feedback for jump if needed (e.g., scale player slightly)
            }
            break;
        case 'ArrowDown': // Slide (Not implemented visually)
        case 's':
            console.log("Slide attempt (visuals not implemented)");
            // TODO: Implement slide mechanic (e.g., scale player Y down, check for low obstacles)
            break;
    }
    // Calculate target X based on lane for smooth transition
    targetPlayerX = (playerLane - 1) * (segmentWidth / 3);
});

// --- Collision Detection (Axis-Aligned Bounding Box - AABB) ---
function checkCollisions() {
    if (!player || obstacles.length === 0) return false; // Basic checks

    const playerBox = new THREE.Box3().setFromObject(player);

    for (let i = obstacles.length - 1; i >= 0; i--) {
        const obstacle = obstacles[i];
        if (!obstacle) continue; // Skip if obstacle somehow undefined

        const obstacleBox = new THREE.Box3().setFromObject(obstacle);

        if (playerBox.intersectsBox(obstacleBox)) {
             console.log(`Collision detected with obstacle at Z: ${obstacle.position.z}`);
             // Check if player is significantly above the obstacle (jumped over)
             // Compare bottom of player bbox with top of obstacle bbox for better check
             if (playerBox.min.y > obstacleBox.max.y - 0.2) { // Allow a small tolerance
                 console.log("Jumped over!");
                 continue; // Considered jumped over, check next obstacle
             } else {
                 console.log("Direct Hit!");
                 return true; // Collision!
             }
        }
    }
    return false; // No collision detected
}


// --- Game Loop ---
let lastObstacleSpawnTime = 0;
const obstacleSpawnInterval = 1000; // Try to spawn roughly every second (adjust)

function animate(time) { // time is provided by requestAnimationFrame
    if (isGameOver) {
        // Show game over screen only once
        if (gameOverElement.style.display !== 'block') {
             gameOverElement.style.display = 'block';
             finalScoreElement.textContent = Math.floor(score);
             console.log("Game Over - Final Score:", Math.floor(score));
        }
        return; // Stop the loop
    }

    const animationId = requestAnimationFrame(animate); // Request next frame early

    // --- Updates ---

    // Smoothly interpolate player X position for lane changes
    player.position.x += (targetPlayerX - player.position.x) * 0.15; // Adjust multiplier for faster/slower lane change

    // Handle Jumping physics
    if (isJumping) {
        player.position.y += jumpVelocity;
        jumpVelocity -= gravity;
        // Check if player has landed (position hits the ground)
        if (player.position.y <= playerHeight / 2) {
            player.position.y = playerHeight / 2; // Snap to ground
            isJumping = false;
            jumpVelocity = 0;
        }
    }

    // Move player forward (or rather, move the world towards the player)
    const deltaSpeed = gameSpeed; // Use current game speed for movement this frame
    player.position.z -= deltaSpeed; // Conceptually, player stays at z=0, world moves

    // Move Camera to follow player
    camera.position.z -= deltaSpeed; // Move camera at the same speed as the player concept

    // Move Lights (optional, but good if the player moves very far)
    // directionalLight.position.z -= deltaSpeed;
    // directionalLight.target.position.copy(player.position); // Ensure light always targets player


    // --- Path Management ---
    pathSegments.forEach((segment, index) => {
        segment.position.z += deltaSpeed; // Move path towards player

        // Procedural Generation: If a segment goes behind camera, move it to the front
        // Check against a point slightly behind the camera to avoid gaps
        if (segment.position.z > camera.position.z + segmentLength) {
            // Move segment far ahead
            segment.position.z -= pathSegments.length * segmentLength;
            lastSegmentZ = segment.position.z; // Update last segment Z for obstacle spawning

            // TODO: Add logic here to potentially change segment type (turn, gap, slope)
            // TODO: Add logic here to clean up obstacles associated with this segment before reusing
        }
    });

     // --- Obstacle Management ---
     obstacles.forEach((obstacle, index) => {
        if (!obstacle) return;
        obstacle.position.z += deltaSpeed; // Move obstacles towards player

         // Remove obstacles that are far behind the player (and off-screen)
        if (obstacle.position.z > camera.position.z + 10) { // Check if well behind camera
             scene.remove(obstacle);
             obstacles.splice(index, 1); // Remove from array AND scene
             console.log("Removed obstacle");
             // TODO: Use object pooling instead of creating/destroying for better performance
         }
     });

    // --- Spawn New Obstacles ---
    // Spawn based on distance or time, ensuring they appear ahead of the player
    const currentTime = time || performance.now(); // Use timestamp from requestAnimationFrame or fallback
    if (currentTime - lastObstacleSpawnTime > obstacleSpawnInterval) {
        if (Math.random() < 0.6) { // % chance to spawn an obstacle this interval
             const randomLane = Math.floor(Math.random() * 3); // 0, 1, or 2
             // Spawn relative to the *last path segment's Z position* + some offset,
             // ensuring it's well ahead of the player's current conceptual Z=0
             const spawnZ = lastSegmentZ - segmentLength/2 + (Math.random() * -segmentLength * 0.5); // Spawn somewhere on the furthest segment
             console.log(`Attempting to spawn obstacle in lane ${randomLane} at Z: ${spawnZ}`);
             createObstacle(randomLane, spawnZ);
             lastObstacleSpawnTime = currentTime;
        }
    }


    // --- Collision Check ---
    if (checkCollisions()) {
        isGameOver = true;
        // Optional: Add visual feedback like changing player color or stopping movement immediately
        playerMaterial.color.set(0x6666ff); // Turn player blue on collision
        // Optional: Cancel the *next* animation frame to prevent one last movement flicker
        // cancelAnimationFrame(animationId);
        // The game over check at the start of animate() will handle stopping.
    }

    // --- Update Score & Difficulty ---
    if (!isGameOver) {
        score += deltaSpeed * 5; // Score based on distance travelled (adjust multiplier)
        scoreElement.textContent = `Score: ${Math.floor(score)}`;

        // Increase game speed gradually
        if (gameSpeed < maxGameSpeed) {
             gameSpeed += speedIncrement;
        }
    }

    // --- Rendering ---
    // controls?.update(); // Update OrbitControls if they are enabled and being used

    try {
        renderer.render(scene, camera);
    } catch (e) {
        console.error("Error during render:", e);
        isGameOver = true; // Stop the loop if rendering fails
    }
}

// --- Resize Handling ---
window.addEventListener('resize', () => {
    // Update camera aspect ratio
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();

    // Update renderer size
    renderer.setSize(window.innerWidth, window.innerHeight);
    console.log("Window resized");
});

// --- Start the Game ---
console.log("Starting animation loop...");
animate(); // Initial call to start the game loop