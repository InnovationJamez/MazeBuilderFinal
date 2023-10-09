const W = 20;
const H = 20;

const DIR = {
    UP: 1,
    DOWN: 2,
    LEFT: 4,
    RIGHT: 8,
    VISIT: 16,
    SOLVE: 32
}

const DIRS = ["U", "D", "L", "R", "V"];

const dirName = (dir) => {
    switch (dir) {
        case DIR.UP:
            return DIRS[0];
        case DIR.DOWN:
            return DIRS[1];
        case DIR.LEFT:
            return DIRS[2];
        case DIR.RIGHT:
            return DIRS[3];
        case DIR.SOLVE:
            return DIRS[4];
    }
}

const dirNames = (dirList) => Array.from(dirList, (dir) => dirName(dir));

const randInt = (num) => Math.floor(Math.random() * num);

const checkPos = (maze, xPos, yPos) => {
    // check if out of bounds
    if (xPos >= W || yPos >= H || xPos < 0 || yPos < 0) {
        return false;
    }
    // check if position is taken
    if ((maze[xPos + yPos * W] & DIR.VISIT) == DIR.VISIT) {
        return false;
    }

    // checks compelte space is open
    return true;
}

const checkNeighbor = (maze, pos) => {
    // list of open directions
    let openDir = [];

    // check right
    if (checkPos(maze, pos.x + 1, pos.y)) {
        // add to open list
        openDir.push(DIR.RIGHT);
    }

    // check left
    if (checkPos(maze, pos.x - 1, pos.y)) {
        // add to open list
        openDir.push(DIR.LEFT);
    }

    // check up
    if (checkPos(maze, pos.x, pos.y + 1)) {
        // add to open list
        openDir.push(DIR.UP);
    }

    // check down 
    if (checkPos(maze, pos.x, pos.y - 1)) {
        // add to open list
        openDir.push(DIR.DOWN);
    }

    return openDir;
}

const walk = (maze, pos, dir) => {
    // walk 
    switch (dir) {
        case DIR.UP:
            maze[pos.y * W + pos.x] |= DIR.UP;
            pos.y++;
            maze[pos.y * W + pos.x] |= DIR.DOWN;
            break;
        case DIR.DOWN:
            maze[pos.y * W + pos.x] |= DIR.DOWN;
            pos.y--;
            maze[pos.y * W + pos.x] |= DIR.UP;
            break;
        case DIR.LEFT:
            maze[pos.y * W + pos.x] |= DIR.LEFT;
            pos.x--;
            maze[pos.y * W + pos.x] |= DIR.RIGHT;
            break;
        case DIR.RIGHT:
            maze[pos.y * W + pos.x] |= DIR.RIGHT;
            pos.x++;
            maze[pos.y * W + pos.x] |= DIR.LEFT;
            break;
    }

    // set pos as visited
    maze[pos.y * W + pos.x] |= DIR.VISIT;
}

const backTrack = (maze) => {
    // travel list
    let travel = [];

    let pos = {
        x: randInt(W),
        y: randInt(H)
    }

    // add initial position
    travel.push(pos);
    // set the initial position as visited
    maze[pos.y * W + pos.x] |= DIR.VISIT;

    let c = 0;

    // start looping
    while (travel.length > 0) {
        let openDir = checkNeighbor(maze, pos);

        if (openDir < 1) {
            // pop off of end
            travel.pop();
            // set new position
            pos = (travel.length > 0) ? travel[travel.length - 1] : -1;
        }
        else {
            // select direction
            let dir = openDir[randInt(openDir.length)];

            // walk 
            walk(maze, pos, dir);
            // add new locaiton
            travel.push({ x: pos.x, y: pos.y });
        }
        let s = "";
    }
}

const prim = () => {

}

