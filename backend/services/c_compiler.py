import subprocess
import json
import os
import tempfile

class CCompiler:
    """Service to compile and execute C programs"""

    def __init__(self):
        self.core_dir = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'core')

    def compile_and_run(self, source_file, input_data=None):
        """
        Compile and run a C program

        Args:
            source_file: Path to C source file
            input_data: Optional JSON input data to pass to the program

        Returns:
            Dictionary with success status and output
        """
        try:
            # Create temporary directory for compilation
            with tempfile.TemporaryDirectory() as temp_dir:
                # Compile the C program
                executable = os.path.join(temp_dir, 'program.exe')
                compile_cmd = ['gcc', source_file, '-o', executable]

                compile_result = subprocess.run(
                    compile_cmd,
                    capture_output=True,
                    text=True,
                    timeout=30
                )

                if compile_result.returncode != 0:
                    return {
                        'success': False,
                        'error': f'Compilation failed: {compile_result.stderr}'
                    }

                # Run the compiled program
                run_cmd = [executable]

                # Pass input data as command-line argument if provided
                if input_data:
                    import shlex
                    run_cmd.append(shlex.quote(json.dumps(input_data)))

                run_result = subprocess.run(
                    run_cmd,
                    capture_output=True,
                    text=True,
                    timeout=30
                )

                if run_result.returncode != 0:
                    return {
                        'success': False,
                        'error': f'Execution failed: {run_result.stderr}'
                    }

                # Parse output as JSON
                try:
                    output = json.loads(run_result.stdout)
                    return {'success': True, 'data': output}
                except json.JSONDecodeError:
                    return {
                        'success': False,
                        'error': f'Invalid JSON output: {run_result.stdout}'
                    }

        except subprocess.TimeoutExpired:
            return {'success': False, 'error': 'Execution timeout'}
        except Exception as e:
            return {'success': False, 'error': str(e)}

    def compile_only(self, source_file):
        """
        Compile a C program without running it

        Args:
            source_file: Path to C source file

        Returns:
            Dictionary with success status
        """
        try:
            executable = source_file.replace('.c', '.exe')
            compile_cmd = ['gcc', source_file, '-o', executable]

            compile_result = subprocess.run(
                compile_cmd,
                capture_output=True,
                text=True,
                timeout=30
            )

            if compile_result.returncode != 0:
                return {
                    'success': False,
                    'error': f'Compilation failed: {compile_result.stderr}'
                }

            return {'success': True, 'executable': executable}

        except Exception as e:
            return {'success': False, 'error': str(e)}
