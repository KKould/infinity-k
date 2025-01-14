module;
#include <filesystem>

import stl;
import memory_pool;
import segment_posting;
import index_segment_reader;
import posting_iterator;
import index_defines;
import index_config;
import inmem_index_segment_reader;
import posting_writer;
import data_block;
import parser;
import column_vector;
import third_party;
import column_indexer;
module indexer;

namespace infinity {
Indexer::Indexer() {}

Indexer::~Indexer() {}

void Indexer::Open(const InvertedIndexConfig &index_config, const String &directory, Vector<u64> &column_ids) {
    index_config_ = index_config;
    String index_name = index_config_.GetIndexName();
    Path path = Path(directory) / index_name;
    directory_ = path.string();
    std::error_code ec;
    bool path_exists = std::filesystem::exists(path);
    if (!path_exists) {
        std::filesystem::create_directories(path, ec);
    }
    byte_slice_pool_.reset(new MemoryPool);
    buffer_pool_.reset(new RecyclePool);
    for (SizeT i = 0; i < column_ids.size(); ++i) {
        u64 column_id = column_ids[i];
        column_indexers_[column_id] = MakeUnique<ColumnIndexer>(column_id, index_config_, byte_slice_pool_, buffer_pool_);
    }
}

void Indexer::Add(DataBlock *data_block) {
    Vector<RowID> row_ids;
    Vector<SharedPtr<ColumnVector>> column_vectors;
    for (SizeT i = 0; i < data_block->column_count(); ++i) {
        SharedPtr<ColumnVector> column_vector = data_block->column_vectors[i];
        if (column_vector->data_type()->type() == LogicalType::kRowID) {
            row_ids.resize(column_vector->Size());
            Memcpy(row_ids.data(), column_vector->data(), column_vector->Size() * sizeof(RowID));
            break;
        } else {
            column_vectors.push_back(column_vector);
        }
    }
    /// TODO column_id ?
    for (SizeT i = 0; i < column_vectors.size(); ++i) {
        u64 column_id = i;
        column_indexers_[column_id]->Add(column_vectors[i], row_ids);
    }
}

void Indexer::Commit() {}

SharedPtr<IndexSegmentReader> Indexer::CreateInMemSegmentReader() { return MakeShared<InMemIndexSegmentReader>(); }
} // namespace infinity
