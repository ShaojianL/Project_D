# pragma once

#include <cstdint>
#include <string>
#include <cstddef>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <optional>
#include <iosfwd>

namespace  Core {
    /**
     * Program metadata
     */
    inline constexpr const char* kProgramName = "natilus";
    inline constexpr const char* kProgramTitle = "Kmer counter";
    inline constexpr const char* kVersionString = "0.1.0";

    /**
     * Output format
     */

    enum class OutputFormat { CSV, Parquet };

    /**
     * Biological alphabet selection
     * DNA : Supports A C G T; optionally N (unknown) and U mapped -> T if enabled
     * Protein: Support the 20 standard amino acids; optionally B, Z, X (ambiguous)
     */

    enum class Alphabet { DNA, Protein };

    /**
     * Controls what to do with the ambiguous or invalid characters while counting
     */

    enum class AmbiguityMode {
        // Break k-mer windows at ambiguous/invalid chars (safer for exact counting)
        Break,
        // Skip ambiguous chars but keep sliding (may bias kmers)
        Skip
    };

    /**
     * Options for normalizing/validating sequences prior to counting
     */

    struct AlphabetOptions {
        Alphabet alphabet = Alphabet::Protein;
        bool to_upper = true;   // normalize to upper case
        bool accept_u_as_t = true;  // DNA: Map "U" to "T"
        bool accept_n = true;   // DNA: allow "N" as ambiguous
        bool accept_bzx = true; // Protein: allow B Z X as ambiguous
        AmbiguityMode ambiguity_mode = AmbiguityMode::Break;
    };

    /**
     * CLI options
     */

    struct Options {
        std::vector<std::filesystem::path> fasta_inputs;    // --fasta-input (file/folder; multiple ok)
        std::optional<std::filesystem::path> list_input;    // --list-input (CSV, one path per row)

        // Core parameters
        std::size_t kmer_size = 0;                          // -s / --size
        std::filesystem::path output_path;                  // -o / --output

        // Filters (whole-number)
        int lower_filter_pct = 0;                           // -l / --lower-filter [default: 0]
        int upper_filter_pct = 100;                         // -u / --upper-filter [default: 100]

        // Output
        OutputFormat format = OutputFormat::Parquet;        // -f / --format [default: parquet]

        // Alphabet (runtime selectable; default Protein; wire to a flag if you want)
        AlphabetOptions alph_opt{}; // init to default values as specified in the struct
    };
}