#include "vm/test/test.hpp"
#include "prelude.hpp"
#include "builtin/nativefunction.hpp"
#include "ffi.hpp"

VM *global_state;

class TestNativeFunction : public CxxTest::TestSuite, public VMTest {
public:

  void setUp() {
    create();
  }

  void tearDown() {
    destroy();
  }

  void test_type_size() {
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_CHAR) == 1);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_UCHAR) == 1);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_SHORT) == 2);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_USHORT) == 2);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_INT) == 4);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_UINT) == 4);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_LONG) >= 4);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_ULONG) >= 4);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_LONG_LONG) >= 8);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_ULONG_LONG) >= 8);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_FLOAT) >= 4);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_DOUBLE) >= 8);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_PTR) >= 4);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_STRING) >= 4);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_STATE) >= 4);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_STRPTR) >= 4);
    TS_ASSERT(NativeFunction::type_size(RBX_FFI_TYPE_OBJECT) >= 4);
  }

  void test_create() {
    NativeFunction* func = NativeFunction::create(state, state->symbol("blah"), 0);
    TS_ASSERT_EQUALS(func->name(), state->symbol("blah"));
  }

  void test_bind_with_string() {
    String* name = String::create(state, "strlen");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_STRING));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_INT);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, name);

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(out->fixnum_p());
    TS_ASSERT_EQUALS(as<Integer>(out)->to_native(), 6);
  }

  void test_bind_with_string_null() {
    String* name = String::create(state, "getcwd");

    Array* args = Array::create(state, 2);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_STRING));
    args->set(state, 1, Fixnum::from(RBX_FFI_TYPE_INT));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_STRING);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 2);
    input->set(state, 0, Qnil);
    input->set(state, 1, Fixnum::from(0));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<String>(out));
  }

  void test_bind_with_char() {
    String* name = String::create(state, "dummy_char");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_CHAR));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_CHAR);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, Fixnum::from(13));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Fixnum>(out));
    TS_ASSERT_EQUALS(as<Fixnum>(out)->to_native(), 13);
  }

  void test_bind_with_unsigned_char() {
    String* name = String::create(state, "dummy_unsigned_char");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_UCHAR));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_UCHAR);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, Fixnum::from(13));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Fixnum>(out));
    TS_ASSERT_EQUALS(as<Fixnum>(out)->to_native(), 13);
  }

  void test_bind_with_short() {
    String* name = String::create(state, "dummy_short");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_SHORT));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_SHORT);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, Fixnum::from(13));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Fixnum>(out));
    TS_ASSERT_EQUALS(as<Fixnum>(out)->to_native(), 13);
  }

  void test_bind_with_unsigned_short() {
    String* name = String::create(state, "dummy_unsigned_short");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_USHORT));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_USHORT);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 2);
    input->set(state, 0, Fixnum::from(0));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Fixnum>(out));

    input = Array::create(state, 2);
    input->set(state, 0, out);

    Arguments args_obj2(input);

    out = func->call(state, args_obj2);

    TS_ASSERT(kind_of<Fixnum>(out));
    TS_ASSERT_EQUALS(out, Fixnum::from(0));
  }

  void test_bind_with_int() {
    String* name = String::create(state, "dummy_int");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_INT));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_INT);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, Fixnum::from(13));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Integer>(out));
    TS_ASSERT_EQUALS(as<Integer>(out)->to_native(), (native_int)13);

    input = Array::create(state, 1);
    input->set(state, 0, Integer::from(state, (int)2147483647));

    Arguments args_obj2(input);

    out = func->call(state, args_obj2);

    TS_ASSERT(kind_of<Integer>(out));
    TS_ASSERT_EQUALS(as<Integer>(out)->to_native(), (native_int)2147483647);
  }

  void test_bind_with_unsigned_int() {
    String* name = String::create(state, "dummy_unsigned_int");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_UINT));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_UINT);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, Fixnum::from(13));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Integer>(out));
    TS_ASSERT_EQUALS(as<Integer>(out)->to_native(), (native_int)13);

    input = Array::create(state, 1);
    input->set(state, 0, Integer::from(state, (unsigned int)2147483647));

    Arguments args_obj2(input);

    out = func->call(state, args_obj2);

    TS_ASSERT(kind_of<Integer>(out));
    TS_ASSERT_EQUALS(as<Integer>(out)->to_native(), (native_int)2147483647);
  }

  void test_bind_with_long() {
    String* name = String::create(state, "dummy_long");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_LONG));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_LONG);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, Fixnum::from(13));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Integer>(out));
    TS_ASSERT_EQUALS(as<Integer>(out)->to_native(), (native_int)13);

    input = Array::create(state, 1);
    input->set(state, 0, Integer::from(state, (long)2147483647));

    Arguments args_obj2(input);

    out = func->call(state, args_obj2);

    TS_ASSERT(kind_of<Integer>(out));
    TS_ASSERT_EQUALS(as<Integer>(out)->to_native(), (native_int)2147483647);
  }

  void test_bind_with_unsigned_long() {
    String* name = String::create(state, "dummy_unsigned_long");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_ULONG));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_ULONG);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, Fixnum::from(13));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Integer>(out));
    TS_ASSERT_EQUALS(as<Integer>(out)->to_native(), (native_int)13);

    input = Array::create(state, 1);
    input->set(state, 0, Integer::from(state, (unsigned long)2147483647));

    Arguments args_obj2(input);

    out = func->call(state, args_obj2);

    TS_ASSERT(kind_of<Integer>(out));
    TS_ASSERT_EQUALS(as<Integer>(out)->to_native(), (native_int)2147483647);
  }

  void test_bind_with_long_long() {
    String* name = String::create(state, "dummy_long_long");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_LONG_LONG));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_LONG_LONG);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, Fixnum::from(13));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Integer>(out));
    TS_ASSERT_EQUALS(as<Integer>(out)->to_native(), (native_int)13);

    input = Array::create(state, 1);
    input->set(state, 0, Integer::from(state, 9223372036854775807LL));

    Arguments args_obj2(input);

    out = func->call(state, args_obj2);

    TS_ASSERT(kind_of<Bignum>(out));
    TS_ASSERT_EQUALS(as<Bignum>(out)->to_long_long(), 9223372036854775807LL);
  }

  void test_bind_with_unsigned_long_long() {
    String* name = String::create(state, "dummy_unsigned_long_long");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_ULONG_LONG));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_ULONG_LONG);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, Fixnum::from(13));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Integer>(out));
    TS_ASSERT_EQUALS(as<Integer>(out)->to_native(), (native_int)13);

    input = Array::create(state, 1);
    input->set(state, 0, Integer::from(state, 9223372036854775808ULL));

    Arguments args_obj2(input);

    out = func->call(state, args_obj2);

    TS_ASSERT(kind_of<Bignum>(out));
    TS_ASSERT_EQUALS(as<Bignum>(out)->to_ulong_long(), 9223372036854775808ULL);
  }

  void test_bind_with_void() {
    String* name = String::create(state, "dummy_void");

    Array* args = Array::create(state, 0);

    Object* ret = Fixnum::from(RBX_FFI_TYPE_VOID);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Arguments args_obj;

    Object* out = func->call(state, args_obj);

    TS_ASSERT_EQUALS(out, Qnil);
  }

  void test_bind_with_ptr() {
    String* name = String::create(state, "dummy_ptr");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_PTR));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_PTR);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    char buffer[1];
    buffer[0] = 0;
    MemoryPointer* ptr = MemoryPointer::create(state, buffer);

    Array* input = Array::create(state, 1);
    input->set(state, 0, ptr);

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<MemoryPointer>(out));
    TS_ASSERT_EQUALS(as<MemoryPointer>(out)->pointer, ptr->pointer);

    input = Array::create(state, 1);
    input->set(state, 0, Qnil);

    Arguments args_obj2(input);

    out = func->call(state, args_obj2);

    TS_ASSERT_EQUALS(out, Qnil);
  }

  void test_bind_with_float() {
    String* name = String::create(state, "dummy_float");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_FLOAT));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_FLOAT);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, Float::create(state, 13.2));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Float>(out));
    TS_ASSERT(as<Float>(out)->val > 13.19);
    TS_ASSERT(as<Float>(out)->val < 13.21);
  }

  void test_bind_with_double() {
    String* name = String::create(state, "dummy_double");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_DOUBLE));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_DOUBLE);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, Float::create(state, 13.2));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Float>(out));
    TS_ASSERT_EQUALS(as<Float>(out)->val, 13.2);
  }

  void test_bind_with_string_returned() {
    String* name = String::create(state, "dummy_string");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_STRING));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_STRING);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    input->set(state, 0, String::create(state, "whatever"));

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<String>(out));
    TS_ASSERT_EQUALS(as<String>(out)->c_str(), std::string("whatever"));

    input = Array::create(state, 1);
    input->set(state, 0, Qnil);

    Arguments args_obj2(input);

    out = func->call(state, args_obj2);

    TS_ASSERT_EQUALS(out, Qnil);
  }

  void test_bind_with_string_and_ptr() {
    Array* args = Array::create(state, 0);

    Object* ret = Fixnum::from(RBX_FFI_TYPE_STRPTR);

    String* name = String::create(state, "static_string");

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Arguments args_obj;

    Array* out = try_as<Array>(func->call(state, args_obj));

    TS_ASSERT(kind_of<Array>(out));

    String* o1 = try_as<String>(out->get(state, 0));
    MemoryPointer* o2 = try_as<MemoryPointer>(out->get(state, 1));
    TS_ASSERT(kind_of<String>(o1));
    TS_ASSERT(kind_of<MemoryPointer>(o2));

    TS_ASSERT_EQUALS(o1->c_str(), std::string("static strings are fun"));
    TS_ASSERT(strcmp((char*)(o2->pointer), "static strings are fun") == 0);
  }

  void test_bind_with_string_and_ptr_for_null() {
    Array* args = Array::create(state, 0);

    Object* ret = Fixnum::from(RBX_FFI_TYPE_STRPTR);

    String* name = String::create(state, "null_string");

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Arguments args_obj;

    Array* out = try_as<Array>(func->call(state, args_obj));

    TS_ASSERT(kind_of<Array>(out));

    TS_ASSERT_EQUALS(out->get(state, 0), Qnil);
    TS_ASSERT_EQUALS(out->get(state, 1), Qnil);
  }

  void test_bind_with_object() {
    String* name = String::create(state, "dummy_ptr");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_OBJECT));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_OBJECT);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Array* input = Array::create(state, 1);
    Object* obj = state->new_object<Object>(G(object));
    input->set(state, 0, obj);

    Arguments args_obj(input);

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Object>(out));
    TS_ASSERT_EQUALS(out, obj);

    input = Array::create(state, 1);
    input->set(state, 0, Qnil);

    Arguments args_obj2(input);

    out = func->call(state, args_obj2);

    TS_ASSERT_EQUALS(out, Qnil);
  }

  void test_bind_with_state() {
    global_state = state;

    String* name = String::create(state, "dummy_state");

    Array* args = Array::create(state, 1);
    args->set(state, 0, Fixnum::from(RBX_FFI_TYPE_STATE));

    Object* ret = Fixnum::from(RBX_FFI_TYPE_INT);

    NativeFunction *func = NativeFunction::bind(state, Qnil, name, args, ret);

    TS_ASSERT(!func->nil_p());

    Arguments args_obj;

    Object* out = func->call(state, args_obj);

    TS_ASSERT(kind_of<Fixnum>(out));
    TS_ASSERT(as<Fixnum>(out)->to_native());
  }

};

extern "C" {

  char dummy_char(char c) {
    return c;
  }

  unsigned char dummy_unsigned_char(unsigned char c) {
    return c;
  }

  short dummy_short(short c) {
    return c;
  }

  unsigned short dummy_unsigned_short(unsigned short c) {
    return c;
  }

  int dummy_int(int c) {
    return c;
  }

  unsigned int dummy_unsigned_int(unsigned int c) {
    return c;
  }

  long dummy_long(long c) {
    return c;
  }

  unsigned long dummy_unsigned_long(unsigned long c) {
    return c;
  }

  long long dummy_long_long(long long c) {
    return c;
  }

  unsigned long long dummy_unsigned_long_long(unsigned long long c) {
    return c;
  }

  float dummy_float(float c) {
    return c;
  }

  double dummy_double(double c) {
    return c;
  }

  void* dummy_ptr(void* c) {
    return c;
  }

  void dummy_void() {
    return;
  }

  char* dummy_string(char* c) {
    return c;
  }

  static char* ss = const_cast<char *>("static strings are fun");
  char* static_string() {
    return ss;
  }

  char* null_string() {
    return NULL;
  }

  int dummy_state(STATE) {
    return global_state == state;
  }
}