Project 04: Path Finding
========================

This project implements a [Dijkstra's Algorithm] to perform rudimentary path
finding on a 2D tile-based map.

[Dijkstra's Algorithm]: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm


Input
-----

    TILES_N
    TILE_NAME_0	TILE_COST_0
    ...
    TILE_NAME_N-1	TILE_COST_N-1

    MAP_ROWS MAP_COLUMNS
    TILE_0_0    ...
    ...

    TRAVELER_START_ROW TRAVELER_START_COL
    TRAVELER_END_ROW   TRAVELER_END_COL

Output
------

    Cost
    [(ROW_0, COL_0), ...]

Benchmark
---------

|N|Elapsed Time|Memory Usage|
|---|---|---|
|10|0.004s|0.01299 MB|
|20|0.0042s|0.0488 MB|
|50|0.007s|0.2989 MB|
|100|0.0174s|1.1885 MB|
|200|0.0578s|4.7355 MB|
|500|0.3548s|27.2535 MB|
|1000|1.4804s|108.8896 MB|
