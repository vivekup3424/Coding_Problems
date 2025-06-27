const gameBoard = document.getElementById('game-board');
const currentPlayerDisplay = document.getElementById('current-player');
const resetButton = document.getElementById('reset-button');
const pvpModeRadio = document.getElementById('pvp');
const pvaiModeRadio = document.getElementById('pvai');
const commentaryDisplay = document.getElementById('commentary');
const gameOverModal = document.getElementById('game-over-modal');
const modalMessage = document.getElementById('modal-message');
const modalResetButton = document.getElementById('modal-reset-button');

// Audio Elements
const dropSound = document.getElementById('dropSound');
const winSound = document.getElementById('winSound');
const drawSound = document.getElementById('drawSound');

const rows = 6;
const cols = 7;
let board = [];
let currentPlayer = 1; // 1 for Player 1 (red), 2 for Player 2 (yellow)
let gameOver = false;
let gameMode = 'pvp'; // 'pvp' or 'pvai'

const AI_PLAYER = 2;
const HUMAN_PLAYER = 1;
const EMPTY = 0;

// Minimax depth - adjust for difficulty vs performance
const MINIMAX_DEPTH = 4; 

const humanComments = [
    "Nice move! Or was it?",
    "Feeling lucky, punk?",
    "Is that your best shot?",
    "Bold move, let's see if it pays off.",
    "Are you even trying?",
    "My grandma plays better than that! (Just kidding... mostly)",
    "That's one way to do it, I guess.",
    "Thinking outside the box, or just outside the board?",
    "You call that strategy?",
    "I've seen worse... but not by much."
];

const aiComments = [
    "Beep boop, calculating domination!",
    "My circuits are tingling with victory!",
    "Resistance is futile, human.",
    "Error 404: Human intelligence not found.",
    "Just according to my calculations. (Which are always correct)",
    "I'm not saying you're bad, but I'm definitely better.",
    "Processing... Oh, you moved? Didn't notice.",
    "My turn. Prepare to be amazed. Or not.",
    "I'm a lean, mean, Connect Four machine!",
    "Another perfect move. Yawn."
];

function getRandomComment(player) {
    if (player === HUMAN_PLAYER) {
        return humanComments[Math.floor(Math.random() * humanComments.length)];
    } else {
        return aiComments[Math.floor(Math.random() * aiComments.length)];
    }
}

function updateCommentary(player) {
    commentaryDisplay.classList.remove('commentary-effect');
    // Force reflow to restart animation
    void commentaryDisplay.offsetWidth;
    commentaryDisplay.textContent = getRandomComment(player);
    commentaryDisplay.classList.add('commentary-effect');
}

function clearCommentary() {
    commentaryDisplay.textContent = '';
    commentaryDisplay.classList.remove('commentary-effect');
}

function createBoard() {
    gameBoard.innerHTML = '';
    board = [];
    for (let r = 0; r < rows; r++) {
        board.push(Array(cols).fill(EMPTY));
        for (let c = 0; c < cols; c++) {
            const cell = document.createElement('div');
            cell.classList.add('cell');
            cell.dataset.row = r;
            cell.dataset.col = c;
            cell.addEventListener('click', () => dropPiece(c));
            gameBoard.appendChild(cell);
        }
    }
    updateCurrentPlayerDisplay();
    clearCommentary();
    hideGameOverModal();
    console.log("Board created/reset.");
}

function updateCurrentPlayerDisplay() {
    currentPlayerDisplay.textContent = `Player ${currentPlayer}'s Turn`;
    currentPlayerDisplay.style.color = currentPlayer === HUMAN_PLAYER ? 'red' : 'yellow';
    console.log(`Current Player: ${currentPlayer}`);
}

function dropPiece(col) {
    console.log(`Attempting to drop piece in column: ${col} for player: ${currentPlayer}`);
    if (gameOver) {
        console.log("Game is over, cannot drop piece.");
        return;
    }

    for (let r = rows - 1; r >= 0; r--) {
        if (board[r][col] === EMPTY) {
            board[r][col] = currentPlayer;
            drawPiece(r, col);
            dropSound.play(); // Play drop sound
            updateCommentary(currentPlayer);
            console.log(`Piece dropped at (${r}, ${col}) by player ${currentPlayer}`);

            const winInfo = checkWin(r, col, currentPlayer);
            if (winInfo.isWin) {
                currentPlayerDisplay.textContent = `Player ${currentPlayer} Wins!`;
                currentPlayerDisplay.style.color = currentPlayer === HUMAN_PLAYER ? 'red' : 'yellow';
                gameOver = true;
                highlightWinningPieces(winInfo.winningPieces);
                showGameOverModal(`Player ${currentPlayer} Wins!`);
                winSound.play(); // Play win sound
                console.log(`Player ${currentPlayer} wins! Game Over.`);
            } else if (checkDraw()) {
                currentPlayerDisplay.textContent = `It's a Draw!`;
                currentPlayerDisplay.style.color = 'black';
                gameOver = true;
                showGameOverModal(`It's a Draw!`);
                drawSound.play(); // Play draw sound
                console.log("It's a Draw! Game Over.");
            } else {
                currentPlayer = currentPlayer === HUMAN_PLAYER ? AI_PLAYER : HUMAN_PLAYER;
                updateCurrentPlayerDisplay();
                if (gameMode === 'pvai' && currentPlayer === AI_PLAYER && !gameOver) {
                    console.log("AI's turn, calling makeAIMove...");
                    setTimeout(makeAIMove, 500); // AI makes a move after a short delay
                }
            }
            return;
        }
    }
    if (gameMode === 'pvp' || (gameMode === 'pvai' && currentPlayer === HUMAN_PLAYER)) {
        console.log(`Column ${col} is full.`);
        alert('Column is full! Choose another column.');
    }
}

function drawPiece(row, col) {
    const cell = gameBoard.querySelector(`[data-row="${row}"][data-col="${col}"]`);
    const piece = document.createElement('div');
    piece.classList.add('piece', `player${board[row][col]}`);
    cell.appendChild(piece);
}

function highlightWinningPieces(pieces) {
    pieces.forEach(p => {
        const cell = gameBoard.querySelector(`[data-row="${p.row}"][data-col="${p.col}"]`);
        if (cell && cell.firstChild) {
            cell.firstChild.classList.add('winning-piece');
        }
    });
}

// --- Board manipulation and check functions for Minimax ---

function getValidMoves(currentBoard) {
    const validMoves = [];
    for (let c = 0; c < cols; c++) {
        if (currentBoard[0][c] === EMPTY) {
            validMoves.push(c);
        }
    }
    console.log("Valid moves for current board state:", validMoves);
    return validMoves;
}

function dropPieceOnBoard(currentBoard, col, player) {
    const newBoard = currentBoard.map(row => [...row]); // Deep copy the board
    for (let r = rows - 1; r >= 0; r--) {
        if (newBoard[r][col] === EMPTY) {
            newBoard[r][col] = player;
            return { newBoard, row: r, col: col };
        }
    }
    return null; // Column is full
}

function checkWin(row, col, player, currentBoard = board) {
    const winningPieces = [];

    // Check horizontal
    for (let c = 0; c <= cols - 4; c++) {
        const window = [];
        for (let i = 0; i < 4; i++) {
            window.push({ row: row, col: c + i, player: currentBoard[row][c + i] });
        }
        if (window.every(p => p.player === player)) {
            return { isWin: true, winningPieces: window };
        }
    }

    // Check vertical
    for (let r = 0; r <= rows - 4; r++) {
        const window = [];
        for (let i = 0; i < 4; i++) {
            window.push({ row: r + i, col: col, player: currentBoard[r + i][col] });
        }
        if (window.every(p => p.player === player)) {
            return { isWin: true, winningPieces: window };
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (let r = 0; r <= rows - 4; r++) {
        for (let c = 0; c <= cols - 4; c++) {
            const window = [];
            for (let i = 0; i < 4; i++) {
                window.push({ row: r + i, col: c + i, player: currentBoard[r + i][c + i] });
            }
            if (window.every(p => p.player === player)) {
                return { isWin: true, winningPieces: window };
            }
        }
    }

    // Check diagonal (bottom-left to top-right)
    for (let r = 3; r < rows; r++) {
        for (let c = 0; c <= cols - 4; c++) {
            const window = [];
            for (let i = 0; i < 4; i++) {
                window.push({ row: r - i, col: c + i, player: currentBoard[r - i][c + i] });
            }
            if (window.every(p => p.player === player)) {
                return { isWin: true, winningPieces: window };
            }
        }
    }

    return { isWin: false, winningPieces: [] };
}

function checkDraw(currentBoard = board) {
    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            if (currentBoard[r][c] === EMPTY) {
                return false; // Still empty cells
            }
        }
    }
    return true; // All cells are filled, and no win
}

function isTerminalNode(currentBoard) {
    // Check for win for either player
    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            if (currentBoard[r][c] !== EMPTY) {
                if (checkWin(r, c, currentBoard[r][c], currentBoard).isWin) {
                    return true;
                }
            }
        }
    }
    // Check for draw
    return checkDraw(currentBoard);
}

function evaluateWindow(window, player) {
    let score = 0;
    const opponent = player === HUMAN_PLAYER ? AI_PLAYER : HUMAN_PLAYER;

    const playerCount = window.filter(cell => cell === player).length;
    const emptyCount = window.filter(cell => cell === EMPTY).length;
    const opponentCount = window.filter(cell => cell === opponent).length;

    if (playerCount === 4) {
        score += 100000; // Winning move
    } else if (playerCount === 3 && emptyCount === 1) {
        score += 100; // Potential win (3 in a row with one empty)
    } else if (playerCount === 2 && emptyCount === 2) {
        score += 10; // Two in a row with two empty
    }

    if (opponentCount === 3 && emptyCount === 1) {
        score -= 1000; // Block opponent's potential win
    }

    return score;
}

function evaluateBoard(currentBoard, player) {
    let score = 0;

    // Prioritize center column
    const centerColumn = [];
    for (let r = 0; r < rows; r++) {
        centerColumn.push(currentBoard[r][Math.floor(cols / 2)]);
    }
    const centerCount = centerColumn.filter(cell => cell === player).length;
    score += centerCount * 3; // Give a slight bonus for pieces in the center

    // Evaluate horizontal, vertical, and diagonal windows
    // Horizontal
    for (let r = 0; r < rows; r++) {
        for (let c = 0; c <= cols - 4; c++) {
            const window = currentBoard[r].slice(c, c + 4);
            score += evaluateWindow(window, player);
        }
    }

    // Vertical
    for (let c = 0; c < cols; c++) {
        for (let r = 0; r <= rows - 4; r++) {
            const window = [];
            for (let i = 0; i < 4; i++) {
                window.push(currentBoard[r + i][c]);
            }
            score += evaluateWindow(window, player);
        }
    }

    // Diagonal (top-left to bottom-right)
    for (let r = 0; r <= rows - 4; r++) {
        for (let c = 0; c <= cols - 4; c++) {
            const window = [];
            for (let i = 0; i < 4; i++) {
                window.push(currentBoard[r + i][c + i]);
            }
            score += evaluateWindow(window, player);
        }
    }

    // Diagonal (bottom-left to top-right)
    for (let r = 3; r < rows; r++) {
        for (let c = 0; c <= cols - 4; c++) {
            const window = [];
            for (let i = 0; i < 4; i++) {
                window.push(currentBoard[r - i][c + i]);
            }
            score += evaluateWindow(window, player);
        }
    }

    return score;
}

function minimax(currentBoard, depth, maximizingPlayer) {
    const validMoves = getValidMoves(currentBoard);
    const isTerminal = isTerminalNode(currentBoard);

    if (depth === 0 || isTerminal) {
        if (isTerminal) {
            // Check for AI win
            for (let r = 0; r < rows; r++) {
                for (let c = 0; c < cols; c++) {
                    if (currentBoard[r][c] === AI_PLAYER && checkWin(r, c, AI_PLAYER, currentBoard).isWin) {
                        console.log(`Minimax: Depth ${depth}, Terminal (AI Win), Value: 100000000000000`);
                        return 100000000000000; // Very high score for AI win
                    }
                    // Check for Human win
                    if (currentBoard[r][c] === HUMAN_PLAYER && checkWin(r, c, HUMAN_PLAYER, currentBoard).isWin) {
                        console.log(`Minimax: Depth ${depth}, Terminal (Human Win), Value: -10000000000000`);
                        return -10000000000000; // Very low score for Human win
                    }
                }
            }
            console.log(`Minimax: Depth ${depth}, Terminal (Draw), Value: 0`);
            return 0; // Draw
        } else { // Depth is zero
            const evalScore = evaluateBoard(currentBoard, AI_PLAYER);
            console.log(`Minimax: Depth ${depth}, Evaluated Score: ${evalScore}`);
            return evalScore;
        }
    }

    if (maximizingPlayer) {
        let value = -Infinity;
        for (let col of validMoves) {
            const result = dropPieceOnBoard(currentBoard, col, AI_PLAYER);
            if (result) {
                value = Math.max(value, minimax(result.newBoard, depth - 1, false));
            }
        }
        console.log(`Minimax: Depth ${depth}, Maximizing Player, Value: ${value}`);
        return value;
    } else { // Minimizing player
        let value = Infinity;
        for (let col of validMoves) {
            const result = dropPieceOnBoard(currentBoard, col, HUMAN_PLAYER);
            if (result) {
                value = Math.min(value, minimax(result.newBoard, depth - 1, true));
            }
        }
        console.log(`Minimax: Depth ${depth}, Minimizing Player, Value: ${value}`);
        return value;
    }
}

function makeAIMove() {
    console.log("AI is making a move...");
    let bestScore = -Infinity;
    let bestCol = -1;
    const validMoves = getValidMoves(board);

    if (validMoves.length === 0) {
        console.log("No valid moves for AI. Board might be full or game over.");
        return;
    }

    for (let col of validMoves) {
        const result = dropPieceOnBoard(board, col, AI_PLAYER);
        if (result) {
            const score = minimax(result.newBoard, MINIMAX_DEPTH - 1, false); // Opponent's turn
            console.log(`AI: Column ${col}, Score: ${score}`);
            if (score > bestScore) {
                bestScore = score;
                bestCol = col;
            }
        }
    }

    console.log(`AI: Best Column: ${bestCol}, Best Score: ${bestScore}`);
    if (bestCol !== -1) {
        dropPiece(bestCol);
    } else {
        // Fallback to random if no best move found (shouldn't happen with validMoves check)
        console.warn("AI: No best column found, falling back to random move.");
        const randomCol = validMoves[Math.floor(Math.random() * validMoves.length)];
        dropPiece(randomCol);
    }
}

function showGameOverModal(message) {
    modalMessage.textContent = message;
    gameOverModal.classList.remove('hidden');
}

function hideGameOverModal() {
    gameOverModal.classList.add('hidden');
}

function resetGame() {
    currentPlayer = HUMAN_PLAYER;
    gameOver = false;
    gameMode = pvpModeRadio.checked ? 'pvp' : 'pvai';
    createBoard();
    console.log(`Game reset. Mode: ${gameMode}`);
}

// Event Listeners
resetButton.addEventListener('click', resetGame);
modalResetButton.addEventListener('click', resetGame);
pvpModeRadio.addEventListener('change', resetGame);
pvaiModeRadio.addEventListener('change', resetGame);

// Initial board creation
createBoard();