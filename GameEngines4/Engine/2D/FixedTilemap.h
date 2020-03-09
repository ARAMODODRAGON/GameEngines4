#ifndef FIXED_TILEMAP_H
#define FIXED_TILEMAP_H

template<typename TILE, int CHUNK_SIZE, int CHUNK_COUNT_X, int CHUNK_COUNT_Y>
class FixedTilemap {
public:

	// chunk class used exclusively within this tilemap
	struct Chunk {

		Chunk() {
			// create tile array
			tiles = new TILE[CHUNK_SIZE * CHUNK_SIZE];
		}

		Chunk(const TILE& clear) {
			// create tile array
			tiles = new TILE[CHUNK_SIZE * CHUNK_SIZE];

			// clear the chunk array with the specified tile
			for (size_t i = 0; i < CHUNK_COUNT_X; i++) {
				for (unsigned int j = 0; j < CHUNK_COUNT_Y; j++) {
					tiles[i * CHUNK_SIZE + j] = clear;
				}
			}
		}

		~Chunk() {
			// delete the tile array
			delete[] tiles;
		}


		void Clear(const TILE& tile) {
			// clear the chunk array with the specified tile
			for (unsigned int i = 0; i < CHUNK_COUNT_X; i++) {
				for (unsigned int j = 0; j < CHUNK_COUNT_Y; j++) {
					tiles[i * CHUNK_SIZE + j] = tile;
				}
			}
		}


		TILE* operator[](int i) {
			return &tiles[i * CHUNK_SIZE];
		}

	private:

		// the tile array
		TILE* tiles;

	};

private:

	// the chunk array
	Chunk* chunks;

public:

	// constructors & destructor
	FixedTilemap() {
		// create chunk array
		chunks = new Chunk[CHUNK_COUNT_X * CHUNK_COUNT_Y];

		// fill the chunk array
		for (unsigned int i = 0; i < CHUNK_COUNT_X; i++) {
			for (unsigned int j = 0; j < CHUNK_COUNT_Y; j++) {
				chunks[i * CHUNK_COUNT_X + j] = Chunk();
			}
		}
	}

	FixedTilemap(const TILE& clear) {
		// create chunk array
		chunks = new Chunk[CHUNK_COUNT_X * CHUNK_COUNT_Y];

		// fill the chunk array
		for (unsigned int i = 0; i < CHUNK_COUNT_X; i++) {
			for (unsigned int j = 0; j < CHUNK_COUNT_Y; j++) {
				chunks[i * CHUNK_COUNT_X + j] = Chunk(clear);
			}
		}
	}

	~FixedTilemap() {
		// delete the chunks array
		delete[] chunks;
	}


	// getters
	Chunk& GetChunk(const int& x, const int& y) {
		return chunks[x][y];
	}

	TILE& GetTile(const int& x, const int& y) {
		return chunks[x / CHUNK_SIZE * CHUNK_COUNT_X + y / CHUNK_SIZE][x][y];
	}


	void test() {
		TILE& tile = GetTile(55, 45);
	}
};


#endif // !FIXED_TILEMAP_H


/* tried to make an iterator

	Iterator GetTile(const int& x, const int& y) {
		return Iterator(chunks[x / CHUNK_SIZE * CHUNK_COUNT_X + y / CHUNK_SIZE][x][y], this);
	}
	
	class Iterator {
	
		// friend of outter class
		template<typename TILE, int CHUNK_SIZE, int CHUNK_COUNT_X, int CHUNK_COUNT_Y>
		friend class FixedTilemap;
	
		// the current tile
		TILE* tile;
		int x, y;
	
		// the Tilemap that this iterator is from
		FixedTilemap* tilemap;
	
		Iterator(TILE* tile_, FixedTilemap* tilemap_, int x_, int y_)
			: tile(tile_), tilemap(tilemap_), x(x_), y(y_) { }
	
	public:
	
	};
*/
