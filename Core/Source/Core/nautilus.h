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

    /**
     * Frequency row ()
     * counts are fixed to uint64_t
     */

    struct FrequencyRow
    {
        /* data */
        std::string kmer;
        std::uint64_t count;    // raw count
        double pct;             // 0..100
    };

    /**
     * KmerCounter: APi with runtime alphabet control
     */
    class KmerCounter{
    public:
        // for convenience
        using count_type = std::uint64_t;
        using map_type = std::unordered_map<std::string, count_type>;

        explicit KmerCounter(std::size_t k, AlphabetOptions alph_opt = {});

        // Adjust alphabet behavior at runtime (affects subsequent additions)
        void set_alphabet_options(const AlphabetOptions& opt) noexcept;
        const AlphabetOptions& alphabet_options() const noexcept;

        // Perf hint
        void reserve(std::size_t n_unique_kmers_hint);

        // Add raw sequence (single sequence payload; header ID not needed here)
        void add_sequence(std::string_view sequence);

        // FASTA ingestion helpers
        void add_fasta_file(const std::filesystem::path& fasta_path);
        void add_fasta_folder(const std::filesystem::path& folder, bool recursive = true);
        void add_fasta_stream(std::istream& in); 

        // CSV list ingestion (one path per row; files or folders)
        void add_list_file(const std::filesystem::path& list_csv_path);

        // Accessors
        std::size_t k() const noexcept;
        const map_type& conts() const noexcept;
        double total_kmers() const noexcept;
        void clear();

        // Frequency table with optional [lower, upper] percentage filter
        std::vector<FrequencyRow> frequency_table(int lower_pct = 0, int upper_pct = 100) const;

        // Writers
        void write_csv(const std::filesystem::path& out, 
                    int lower_pct = 0, int upper_pct = 100) const;

        void write_parquet(const std::filesystem::path& out,
                    int lower_pct = 0, int upper_pct = 100) const;
        
        /**
         * Static helpers
         */
        
        // Validate a single character for the given alphabet options
        static bool is_valid_char(char c, const AlphabetOptions& opt) noexcept;

        // Normalize a char according to options (e.g., to_upper, U->T)
        static char normalize_char(char c, const AlphabetOptions& opt) noexcept;

    // Declared after public functions because I want to use count_type, and map_type
    private:
        std::size_t k_{0};
        map_type counts_{};
        double total_{0.0};
        AlphabetOptions alph_opt_{};

        // Internal helpers
        void add_cleaned_sequence(std::string_view sequence);
        void add_path(const std::filesystem::path& p);
        static bool is_ambiguous(char c, const AlphabetOptions& opt) noexcept;

    };
    
}