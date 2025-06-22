from evaluate import evaluate_regression
import numpy as np

def test_evaluate_regression():
    y_true = np.array([3.0, 4.0, 5.0])
    y_pred = np.array([2.5, 4.5, 5.0])
    metrics = evaluate_regression(y_true, y_pred)
    assert 'MSE' in metrics and 'RMSE' in metrics and 'R2' in metrics
    assert abs(metrics['MSE'] - ((0.5**2 + 0.5**2 + 0**2)/3)) < 1e-6
