import subprocess
import pytest


@pytest.mark.parametrize("test_function", [
    "test_allocate_integer_valid_pointer",
    "test_allocate_integer_correct_size",
    "test_allocate_integer_set_value",
    "test_deallocate_integer_frees_memory"
])
def test_c_functions(test_function):
    result = subprocess.run(["./my_tests", test_function], capture_output=True, text=True)

    # Check return code for pass/fail
    assert result.returncode == 0, f"Test '{test_function}' failed: {result.stderr}"

    # Optionally, check stdout/stderr for specific messages
    # assert "Expected output" in result.stdout


if __name__ == "__main__":
    pytest.main([__file__])
