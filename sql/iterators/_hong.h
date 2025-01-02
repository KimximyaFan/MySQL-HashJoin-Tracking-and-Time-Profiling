#define BILLION 1000000000

#define Time_Check(timevalue, total_time, total_count) do {             \
                                                                        \
        unsigned long long timedelay, time1, time2;                     \
                                                                        \
        struct timespec *myclock = (struct timespec*)timevalue;         \
                                                                        \
        time1 = myclock[0].tv_sec * BILLION + myclock[0].tv_nsec;       \
        time2 = myclock[1].tv_sec * BILLION + myclock[1].tv_nsec;       \
        timedelay = time2 - time1;                                      \
                                                                        \
        __sync_fetch_and_add(total_time, timedelay);                    \
        __sync_fetch_and_add(total_count, 1);                           \
} while(0)


#define Count_Up(count) do { \
        __sync_fetch_and_add(count, 1); \
} while(0)

/*
// check for hash join functions
extern unsigned long long int hash_join_chunk_constructor_count;
extern unsigned long long int hash_join_chunk_destructor_count;
extern unsigned long long int hash_join_row_buffer_store_row_count;
extern unsigned long long int hash_join_iterator_read_row_from_probe_iterator_count;
*/

// check for TPC-H Query 3
extern unsigned long long int do_command_count;
extern unsigned long long int unknown_query_time;
extern unsigned long long int hash_join_query_time;

extern struct timespec the_time[2];


// check for Hash Join Buffer Store Row
extern unsigned long long int buffer_store_row_count;
extern unsigned long long int key_hasher_operator_2_count;
extern unsigned long long int buffer_store_immutable_string_count;
extern unsigned long long int hash_join_buffer_store_row_time;

extern struct timespec the_time_2[2];


// check for Hash Join Read Row From Probe Iterator
extern unsigned long long int read_row_from_probe_iterator_count;
extern unsigned long long int read_next_joined_row_from_hashtable_count;

extern unsigned long long int hash_join_read_row_from_probe_iterator_time;
extern unsigned long long int hash_join_read_hashtable_time;
extern unsigned long long int hash_join_total_time;

extern struct timespec the_time_3[2];


// checking internal of ReadRowFromProbeIterator()
extern unsigned long long int read_row_m_probe_input_read_count;
extern unsigned long long int read_row_m_probe_input_read_time;

extern unsigned long long int read_row_result_is_1_count;
extern unsigned long long int read_row_result_is_1_time;

extern unsigned long long int read_row_result_is_0_count;
extern unsigned long long int read_row_result_is_0_time;

extern unsigned long long int read_row_end_psi_batch_count;
extern unsigned long long int read_row_end_psi_batch_time;

extern unsigned long long int read_row_allow_spill_disk_is_true_count;
extern unsigned long long int read_row_allow_spill_disk_is_true_time;

extern unsigned long long int read_row_reading_saving_file_is_true_count;
extern unsigned long long int read_row_reading_saving_file_is_true_time;

extern unsigned long long int read_row_build_hash_table_is_true_count;
extern unsigned long long int read_row_build_hash_table_is_true_time;

extern unsigned long long int read_row_state_setting_count;
extern unsigned long long int read_row_state_setting_time;

extern unsigned long long int read_row_total_count;
extern unsigned long long int read_row_total_time;

extern unsigned long long int print_lock;

extern struct timespec the_time_4[2];

// the longest time for ReadRowFromProbeIterator() is m_probe_input->Read()
// m_probe_input->Read() is TableScanIterator::Read()
// check for TableScanIterator::Read()

extern bool table_scan_check;

extern unsigned long long int table_scan_iter_condition_is_true_while_count;
extern unsigned long long int table_scan_iter_condition_is_true_while_time;

extern unsigned long long int table_scan_iter_condition_is_true_ha_rnd_next_count;
extern unsigned long long int table_scan_iter_condition_is_true_ha_rnd_next_time;

extern unsigned long long int table_scan_iter_condition_is_false_while_count;
extern unsigned long long int table_scan_iter_condition_is_false_while_time;

extern unsigned long long int table_scan_iter_condition_is_false_ha_rnd_next_count;
extern unsigned long long int table_scan_iter_condition_is_false_ha_rnd_next_time;

extern unsigned long long int table_scan_iter_condition_is_false_remainder_count;
extern unsigned long long int table_scan_iter_condition_is_false_remainder_time;

extern struct timespec the_time_5[2];
extern struct timespec the_time_6[2];


extern unsigned long long int ha_rnd_next_has_gcol_time;
extern unsigned long long int ha_rnd_next_has_gcol_count;

extern unsigned long long int ha_rnd_next_table_lock_and_rnd_next_time;
extern unsigned long long int ha_rnd_next_table_lock_and_rnd_next_count;

extern unsigned long long int ha_rnd_next_update_generated_field_time;
extern unsigned long long int ha_rnd_next_update_generated_field_count;

extern unsigned long long int ha_rnd_next_set_row_status_from_handler_time;
extern unsigned long long int ha_rnd_next_set_row_status_from_handler_count;

extern struct timespec the_time_7[2];


// ha_innodb, rnd_next()
extern unsigned long long int innodb_rnd_next_index_first_time;
extern unsigned long long int innodb_rnd_next_index_first_count;

extern unsigned long long int innodb_rnd_next_general_fetch_time;
extern unsigned long long int innodb_rnd_next_general_fetch_count;

extern struct timespec the_time_8[2];


// ha_innodb, general_fetch()
extern unsigned long long int row_search_mvcc_time;
extern unsigned long long int row_search_mvcc_count;

extern unsigned long long int row_search_no_mvcc_time;
extern unsigned long long int row_search_no_mvcc_count;

extern struct timespec the_time_9[2];
