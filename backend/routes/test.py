from flask import Blueprint, jsonify
import os
import sys

# Add services to path
sys.path.append(os.path.join(os.path.dirname(os.path.dirname(__file__)), 'services'))
from c_compiler import CCompiler

test_bp = Blueprint('test', __name__)

@test_bp.route('/test/c-integration', methods=['GET'])
def test_c_integration():
    """Test C program integration"""
    compiler = CCompiler()

    # Path to test C program
    core_dir = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'core')
    source_file = os.path.join(core_dir, 'src', 'test_integration.c')

    if not os.path.exists(source_file):
        return jsonify({
            'success': False,
            'error': f'C source file not found: {source_file}'
        })

    # Compile and run the C program
    result = compiler.compile_and_run(source_file)

    return jsonify(result)
