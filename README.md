## TETRIS

## setup

```
docker build -t ubuntu-tetris:latest .
docker run --rm -d -it --name tetris -v $(pwd):/var/dev ubuntu-tetris:latest
docker exec -it tetris bash
```

### libs
* https://github.com/SFML/SFML/releases
