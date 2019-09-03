
#if HAS_STDIOSTREAM
#undef std
#include <iostream>
using std::cout;
#define std stdx
#define SILENT_TEST 1
#else 
#define SILENT_TEST 1
#endif

#include "pwe_serial.h"

setl::Period<int, setl::TimeUnit::MICROS> s;

#include "assert_that.h"
#include "setl_test_framework.h"

#include "setlx_cstdlib.h" 


namespace pwe_tests_only {
using setl_test::assertThat;

setl::PweBitCollector<15> word_15s;
setl::PweBitCollector<2> word_2s;
setl::PweBitCollectorArray<char, 15> array_15s;
setl::PweBitCollectorArray<char, 2> array_2s;


 struct PWE_TEST_DO_NOT_USE : setl_test::SetlTest
 {

   struct TestBasics {

     TestBasics() {
       do_test_basics();
       do_test_encoder();
       do_test_encoder_decoder();
     }

     using EncoderT = setl::PweEncoder<
       setl::PweBitCollector<15>,
       false,
       false>;

     using DecoderT = setl::PweDecoder<
       setl::PweBitCollector<15>,
       false,
       false>;

     using PeriodType = EncoderT::PeriodType;
     using TimeType = DecoderT::TimeType;
     using PollResult = EncoderT::PollResult;

     void do_test_basics() {

     }

     void do_test_encoder() {
       decoder.reset();

       assertThat(decoder.pollDataReady()).isFalse();
       EncoderT::value_type value = 0x5A;

       TimeType clock;
       auto poll_result = encoder.poll(clock);
       assertThat(poll_result.no_data).eq(true);

       assertThat(encoder.send(value)).isTrue();

       for (int i = 0; i < EncoderT::size_bits; ++i) {

         clock = poll_result.time_next_poll - PeriodType(1);

         poll_result = encoder.poll(clock);
         assertThat(poll_result.current_output).eq(true);
         assertThat(poll_result.no_data).eq(false);

         clock = poll_result.time_next_poll;

         auto poll_result2 = encoder.poll(clock);
         assertThat(poll_result.time_next_poll != poll_result2.time_next_poll).isTrue();
         assertThat(poll_result2.current_output).eq(false);
         assertThat(poll_result2.no_data).eq(false);

         clock = poll_result2.time_next_poll - PeriodType(1);

         poll_result = encoder.poll(clock);
         assertThat(poll_result.time_next_poll == poll_result2.time_next_poll).isTrue();
         assertThat(poll_result.current_output).eq(false);
         assertThat(poll_result.no_data).eq(false);

         clock = poll_result2.time_next_poll;

         if (i < (EncoderT::size_bits - 1)) {
           poll_result2 = encoder.poll(clock);
           assertThat(poll_result.time_next_poll != poll_result2.time_next_poll).isTrue();
           assertThat(poll_result2.current_output).eq(true);
           assertThat(poll_result2.no_data).eq(false);

           clock = poll_result2.time_next_poll - PeriodType(1);

           poll_result = encoder.poll(clock);
           assertThat(poll_result.time_next_poll == poll_result2.time_next_poll).isTrue();
           assertThat(poll_result.current_output).eq(true);
           assertThat(poll_result.no_data).eq(false);
         }
       }

       clock = poll_result.time_next_poll - PeriodType(1);
       auto poll_result2 = encoder.poll(clock);
       assertThat(poll_result.time_next_poll == poll_result2.time_next_poll).isTrue();
       assertThat(poll_result2.current_output).eq(false);
       assertThat(poll_result2.no_data).eq(false);

       clock = poll_result2.time_next_poll;

       poll_result2 = encoder.poll(clock);
       assertThat(poll_result.time_next_poll != poll_result2.time_next_poll).isTrue();
       assertThat(poll_result2.current_output).eq(false);
       assertThat(poll_result2.no_data).eq(false);

       clock = poll_result2.time_next_poll;
       
       // End of stop
       poll_result2 = encoder.poll(clock);
       assertThat(poll_result.time_next_poll != poll_result2.time_next_poll).isTrue();
       assertThat(poll_result2.current_output).eq(false);
       assertThat(poll_result2.no_data).eq(true);

       // no data
       poll_result = encoder.poll(clock);
       assertThat(poll_result.current_output).eq(false);
       assertThat(poll_result.no_data).eq(true);
     }

#if SILENT_TEST
     void print(const PollResult) {
     }
#else
     void print(const PollResult& poll_result) {
       cout << "\n" << poll_result.time_next_poll.get()
         << "," << unsigned(poll_result.current_output)
         << "," << (poll_result.time_next_poll - prev_result.time_next_poll).get();
       prev_result = poll_result;
     }
#endif

     void do_transfer(const EncoderT::value_type& value) {
       const auto& params = setl::PweWaveformParams1to3<TimeType::type, 1000, 1000, 100>;

       // Decoder ignores everything for at least a stop period.
       decoder.signalChanged(jitterTime(), false);
       clock += params.stop_period;

       assertThat(encoder.send(value)).isTrue();

       auto poll_result = encoder.poll(clock);
       print(poll_result);
       int data_ready = 0;
       while (!poll_result.no_data) {
         data_ready += decoder.pollDataReady() ? 1 : 0;
         assertThat(data_ready <= 1).isTrue();
         decoder.signalChanged(jitterTime(), poll_result.current_output);
         clock = poll_result.time_next_poll;
         poll_result = encoder.poll(clock);
         print(poll_result);
       }

       EncoderT::value_type result;
       assertThat(decoder.readValue(result)).isTrue();
       decoder.signalChanged(jitterTime(), poll_result.current_output);

       assertThat(result).eq(value);
     }

     TimeType jitterTime() {
       auto result = clock + PeriodType(std::rand() % 13);
       return result;
     }

     void do_test_encoder_decoder() {
       encoder.reset();
       decoder.reset();

       do_transfer(0x15f);
       do_transfer(0x35a);
       do_transfer(0x300);
       do_transfer(0x299);
       for (std::uint16_t i = 0; i < (1u << 15); ++i) {
         do_transfer(i);
       }
     }

     PollResult prev_result;
     TimeType clock;

     DecoderT decoder{ setl::PweWaveformParams1to3<TimeType::type, 1000, 1000, 100> };
     EncoderT encoder{ setl::PweWaveformParams1to3<TimeType::type, 1000, 1000, 100> };
   };

   bool run() override {
     TestBasics basicsTest;
     return true;
   }
 };

 PWE_TEST_DO_NOT_USE PweTest;

}