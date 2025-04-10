import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';

// --- Game Settings ---
const projectileSpeed = 40; // Faster projectiles
const projectileRadius = 0.1;
const projectileLength = 0.8; // For capsule shape
const targetRadius = 1.0;
const bonusTargetRadius = 0.6; // Smaller bonus targets
const spawnInterval = 1200; // ms (Spawn slightly faster)
const maxTargets = 12;
const projectileMaxDistance = 150;
const targetSpawnRange = 25; // Spawn further out
const targetMaxSpeed = 3.0;
const targetMinSpeed = 1.0;
const bonusTargetMultiplier = 2.5; // Faster bonus targets
const worldBoundary = 30; // Where targets bounce
const bonusTargetChance = 0.2; // 20% chance for a bonus target

// --- Game State ---
let score = 0;
let shotsFired = 0;
let hits = 0;
const scoreElement = document.getElementById('score-display');
const accuracyElement = document.getElementById('accuracy-display');
const clock = new THREE.Clock();
let screenShakeIntensity = 0;

// --- Scene Objects ---
const targets = [];
const projectiles = [];
const particles = []; // For hit effects

// --- Raycasting (Used for shooting direction relative to center screen) ---
const raycaster = new THREE.Raycaster();
// No 'mouse' needed here, we shoot from center

// --- Basic Setup ---
const scene = new THREE.Scene();
scene.background = new THREE.Color(0x111820); // Dark blueish grey
scene.fog = new THREE.Fog(scene.background, camera.near + 15, camera.far - 100); // Add fog

const camera = new THREE.PerspectiveCamera(60, window.innerWidth / window.innerHeight, 0.1, 500); // Adjusted FOV/Far
camera.position.z = 0; // Player at origin

const canvas = document.getElementById('webgl-canvas');
const renderer = new THREE.WebGLRenderer({ canvas: canvas, antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
renderer.shadowMap.enabled = true; // Enable shadows if lights cast them
renderer.shadowMap.type = THREE.PCFSoftShadowMap;

// --- Lighting ---
scene.add(new THREE.AmbientLight(0x606060)); // Dimmer ambient

const dirLight = new THREE.DirectionalLight(0xffffff, 1.5);
dirLight.position.set(15, 20, 10);
dirLight.castShadow = true; // Light casts shadow
dirLight.shadow.mapSize.width = 1024;
dirLight.shadow.mapSize.height = 1024;
dirLight.shadow.camera.near = 0.5;
dirLight.shadow.camera.far = 100;
dirLight.shadow.camera.left = -worldBoundary;
dirLight.shadow.camera.right = worldBoundary;
dirLight.shadow.camera.top = worldBoundary;
dirLight.shadow.camera.bottom = -worldBoundary;
scene.add(dirLight);
// scene.add( new THREE.CameraHelper( dirLight.shadow.camera ) ); // Helper to visualize shadow frustum

// Muzzle flash light
const muzzleFlashLight = new THREE.PointLight(0xffcc66, 5, 10, 2); // Orange-yellow, intense, short range
muzzleFlashLight.visible = false;
muzzleFlashLight.castShadow = false;
camera.add(muzzleFlashLight); // Add to camera so it's always in front
muzzleFlashLight.position.set(0, 0, -0.5); // Slightly in front of camera
scene.add(camera); // Add camera to scene (needed for camera-relative lights)


// --- Controls ---
// OrbitControls are now mainly for debugging or a different mode.
// We'll use pointer lock for FPS-style aiming.
const controls = new OrbitControls(camera, renderer.domElement);
controls.enabled = false; // Disable orbit controls by default for FPS mode
controls.enableDamping = true;
controls.dampingFactor = 0.05;
// To enable OrbitControls again for testing:
// canvas.addEventListener('click', () => { controls.enabled = true; /* ... remove pointer lock? */ });


// Pointer Lock for FPS Controls
let isPointerLocked = false;
canvas.addEventListener('click', () => {
    if (!isPointerLocked) {
        canvas.requestPointerLock = canvas.requestPointerLock || canvas.mozRequestPointerLock;
        canvas.requestPointerLock();
    }
});

document.addEventListener('pointerlockchange', lockChangeAlert, false);
document.addEventListener('mozpointerlockchange', lockChangeAlert, false);

function lockChangeAlert() {
    if (document.pointerLockElement === canvas || document.mozPointerLockElement === canvas) {
        console.log('Pointer Lock active.');
        isPointerLocked = true;
        document.addEventListener("mousemove", updateCameraRotation, false);
    } else {
        console.log('Pointer Lock released.');
        isPointerLocked = false;
        document.removeEventListener("mousemove", updateCameraRotation, false);
        // Optionally re-enable OrbitControls here if desired
        // controls.enabled = true;
    }
}

const euler = new THREE.Euler(0, 0, 0, 'YXZ'); // To control camera rotation
const PI_2 = Math.PI / 2;

function updateCameraRotation(event) {
    if (!isPointerLocked) return;
    const movementX = event.movementX || event.mozMovementX || 0;
    const movementY = event.movementY || event.mozMovementY || 0;

    euler.setFromQuaternion(camera.quaternion);
    euler.y -= movementX * 0.002;
    euler.x -= movementY * 0.002;
    euler.x = Math.max(-PI_2, Math.min(PI_2, euler.x)); // Clamp vertical rotation
    camera.quaternion.setFromEuler(euler);
}


// --- Geometries & Materials ---
const targetMaterial = new THREE.MeshStandardMaterial({
    color: 0xff4444, // Brighter Red
    roughness: 0.5,
    metalness: 0.2
});
const bonusTargetMaterial = new THREE.MeshStandardMaterial({
    color: 0x4488ff, // Blue
    roughness: 0.4,
    metalness: 0.4,
    emissive: 0x224488, // Slight glow
    emissiveIntensity: 0.5
});
const targetGeometry = new THREE.SphereGeometry(targetRadius, 24, 16);
const bonusTargetGeometry = new THREE.SphereGeometry(bonusTargetRadius, 16, 12);

// Projectile: Capsule shape for implied trail
const projectileGeometry = new THREE.CapsuleGeometry(projectileRadius, projectileLength, 4, 8);
const projectileMaterial = new THREE.MeshStandardMaterial({
    color: 0xffff66,
    emissive: 0xffff00,
    emissiveIntensity: 1.5,
    roughness: 0.8,
    metalness: 0.1
});

// Particle Material
const particleMaterial = new THREE.MeshBasicMaterial({
    color: 0xffaa00, // Orange particles
    transparent: true,
    opacity: 0.8
});


// --- Game Logic Functions ---

function updateUI() {
    scoreElement.innerText = `Score: ${score}`;
    const accuracy = shotsFired > 0 ? ((hits / shotsFired) * 100).toFixed(1) : 'N/A';
    accuracyElement.innerText = `Accuracy: ${accuracy}% (${hits}/${shotsFired})`;
}

function spawnTarget() {
    if (targets.length >= maxTargets) return;

    const isBonus = Math.random() < bonusTargetChance;
    const geometry = isBonus ? bonusTargetGeometry : targetGeometry;
    const material = isBonus ? bonusTargetMaterial : targetMaterial;
    const radius = isBonus ? bonusTargetRadius : targetRadius;
    const points = isBonus ? 5 : 1; // Points value

    const target = new THREE.Mesh(geometry, material.clone()); // Clone material for potential individual effects
    target.castShadow = true;
    target.receiveShadow = true;

    // Spawn in a spherical shell area around the origin
    const spawnRadius = targetSpawnRange * (0.6 + Math.random() * 0.4);
    const theta = Math.random() * Math.PI * 2;
    const phi = Math.acos((Math.random() * 2) - 1);
    target.position.set(
        spawnRadius * Math.sin(phi) * Math.cos(theta),
        spawnRadius * Math.sin(phi) * Math.sin(theta), // Use sin for Y to spread more evenly
        spawnRadius * Math.cos(phi)
    );

    // Ensure target isn't *too* close to the camera or other targets (basic check)
    if (target.position.length() < 5 || targets.some(t => t.position.distanceTo(target.position) < radius * 3)) {
        // Simple retry - could be more robust, might fail if space is crowded
        setTimeout(spawnTarget, 50); // Retry slightly later
        return;
    }

    // Assign movement velocity
    const speed = targetMinSpeed + Math.random() * (targetMaxSpeed - targetMinSpeed) * (isBonus ? bonusTargetMultiplier : 1);
    target.userData = {
        velocity: new THREE.Vector3(
            (Math.random() - 0.5),
            (Math.random() - 0.5),
            (Math.random() - 0.5)
        ).normalize().multiplyScalar(speed),
        radius: radius,
        points: points,
        pulseSpeed: 1.0 + Math.random() * 1.5, // For pulsing effect
        pulseAmount: 0.05 + Math.random() * 0.05
    };

    scene.add(target);
    targets.push(target);
}

function fireMuzzleFlash() {
    muzzleFlashLight.visible = true;
    muzzleFlashLight.intensity = 5 + Math.random() * 3; // Vary intensity slightly
    setTimeout(() => {
        muzzleFlashLight.visible = false;
    }, 60); // Flash duration (ms)
}

function shootProjectile() {
    if (!isPointerLocked) return; // Only shoot when pointer is locked

    shotsFired++;
    updateUI();
    fireMuzzleFlash();

    const projectile = new THREE.Mesh(projectileGeometry, projectileMaterial);
    projectile.castShadow = true; // Small effect but why not

    // Get direction from camera center (where the crosshair is)
    // No need for raycaster from mouse click anymore if pointer locked
    const camDir = new THREE.Vector3();
    camera.getWorldDirection(camDir);

    // Set Initial Position slightly in front of the camera
    projectile.position.copy(camera.position).addScaledVector(camDir, 1.0);

    // Align capsule rotation to direction
    projectile.quaternion.setFromUnitVectors(new THREE.Vector3(0, 1, 0), camDir); // Align Y axis of capsule

    projectile.userData.direction = camDir; // Store direction for movement

    scene.add(projectile);
    projectiles.push(projectile);
}

function createHitParticles(position, color = 0xffaa00) {
    const count = 8 + Math.floor(Math.random() * 5); // 8-12 particles
    const particleSize = 0.1 + Math.random() * 0.1;
    const particleGeometry = new THREE.BoxGeometry(particleSize, particleSize, particleSize); // Small cubes

    for (let i = 0; i < count; i++) {
        const pMaterial = particleMaterial.clone(); // Clone to change color/opacity individually
        pMaterial.color.setHex(color);
        const particle = new THREE.Mesh(particleGeometry, pMaterial);
        particle.position.copy(position);

        const velocity = new THREE.Vector3(
            (Math.random() - 0.5),
            (Math.random() - 0.5),
            (Math.random() - 0.5)
        ).normalize().multiplyScalar(5 + Math.random() * 5); // Outward burst speed

        particle.userData = {
            velocity: velocity,
            lifetime: 0.5 + Math.random() * 0.5, // 0.5 - 1.0 seconds duration
            initialLifetime: particle.userData.lifetime // Store initial for fading
        };
        scene.add(particle);
        particles.push(particle);
    }
}

function triggerScreenShake(intensity = 0.05, duration = 0.1) {
     // Simple shake: just set intensity, animation loop handles decay
     screenShakeIntensity = Math.max(screenShakeIntensity, intensity);
     // More complex: store intensity and duration, decay over time in animate loop
}


function updateTargets(deltaTime) {
    const baseScale = 1.0;
    const time = clock.elapsedTime;

    for (let i = targets.length - 1; i >= 0; i--) {
        const target = targets[i];
        const userData = target.userData;

        // Movement & Bounce
        target.position.addScaledVector(userData.velocity, deltaTime);

        // Simple Axis-Aligned Bouncing
        if (Math.abs(target.position.x) > worldBoundary - userData.radius) {
            target.position.x = Math.sign(target.position.x) * (worldBoundary - userData.radius);
            userData.velocity.x *= -1;
        }
        if (Math.abs(target.position.y) > worldBoundary - userData.radius) {
            target.position.y = Math.sign(target.position.y) * (worldBoundary - userData.radius);
            userData.velocity.y *= -1;
        }
        if (Math.abs(target.position.z) > worldBoundary - userData.radius) {
            target.position.z = Math.sign(target.position.z) * (worldBoundary - userData.radius);
            userData.velocity.z *= -1;
        }

        // Pulsing Effect
        const pulse = Math.sin(time * userData.pulseSpeed) * userData.pulseAmount;
        target.scale.setScalar(baseScale + pulse);
    }
}

function updateProjectiles(deltaTime) {
     for (let i = projectiles.length - 1; i >= 0; i--) {
        const proj = projectiles[i];
        proj.position.addScaledVector(proj.userData.direction, projectileSpeed * deltaTime);

        // Remove if too far
        if (proj.position.length() > projectileMaxDistance) {
            scene.remove(proj);
            projectiles.splice(i, 1);
        }
    }
}

function updateParticles(deltaTime) {
    for (let i = particles.length - 1; i >= 0; i--) {
        const p = particles[i];
        p.userData.lifetime -= deltaTime;

        if (p.userData.lifetime <= 0) {
            scene.remove(p);
            particles.splice(i, 1);
        } else {
            p.position.addScaledVector(p.userData.velocity, deltaTime);
            p.userData.velocity.multiplyScalar(0.98); // Air drag
            p.material.opacity = (p.userData.lifetime / p.userData.initialLifetime) * 0.8; // Fade out
            const scale = (p.userData.lifetime / p.userData.initialLifetime);
            p.scale.setScalar(Math.max(0.01, scale)); // Shrink
        }
    }
}


function checkCollisions() {
     for (let i = projectiles.length - 1; i >= 0; i--) {
        const proj = projectiles[i];
        let projectileRemoved = false;

        for (let j = targets.length - 1; j >= 0; j--) {
            const target = targets[j];
            const distance = proj.position.distanceTo(target.position);
            const combinedRadius = target.userData.radius + projectileRadius * 2; // Give projectile a bit more leeway

            if (distance < combinedRadius) {
                // --- HIT ---
                hits++;
                score += target.userData.points;
                updateUI();
                triggerScreenShake(0.04); // Trigger shake on hit

                // Hit Effects
                createHitParticles(target.position.clone(), target.material.color.getHex()); // Pass color

                // Remove target
                scene.remove(target);
                targets.splice(j, 1);

                // Remove projectile
                scene.remove(proj);
                projectiles.splice(i, 1);
                projectileRemoved = true;
                break; // Projectile is gone, stop checking targets for it
            }
        }
    }
}


// --- Event Listeners ---

window.addEventListener('resize', () => {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
});

// Use 'pointerdown' for shooting when pointer is locked
window.addEventListener('pointerdown', (event) => {
    // Check if the click is on the canvas and pointer is locked
    if (isPointerLocked && event.target === canvas) {
         // 0 = left click, 1 = middle, 2 = right
        if (event.button === 0) {
             shootProjectile();
        }
    }
});

// --- Initialization ---
updateUI();
setInterval(spawnTarget, spawnInterval);
// Initial targets
for(let i=0; i< 5; i++) {
    setTimeout(spawnTarget, Math.random() * spawnInterval); // Stagger initial spawns
}

// --- Animation Loop ---
const animate = () => {
    requestAnimationFrame(animate);
    const deltaTime = clock.getDelta();

    // Update Controls (if using damping, though we disabled OrbitControls)
    // controls.update(); // Only needed if OrbitControls are enabled AND use damping

    // Update Game Objects
    updateTargets(deltaTime);
    updateProjectiles(deltaTime);
    updateParticles(deltaTime);

    // Check for Hits
    checkCollisions();

    // Apply Screen Shake
    if (screenShakeIntensity > 0) {
        const shakeAmount = screenShakeIntensity * 0.5; // Reduce shake effect intensity
        camera.position.x += (Math.random() - 0.5) * shakeAmount;
        camera.position.y += (Math.random() - 0.5) * shakeAmount;
        screenShakeIntensity *= 0.9; // Decay shake intensity
        if (screenShakeIntensity < 0.001) {
            screenShakeIntensity = 0;
        }
    }

    // Render
    renderer.render(scene, camera);
};

// Start the game loop
animate();